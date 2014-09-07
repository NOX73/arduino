module Arduino.Controller (
  start
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
import System.Log.Logger (errorM, infoM, rootLoggerName)
import Arduino.DevicePath ( devicePath )
import Control.Monad (forever)

import System.IO
import System.Hardware.Serialport as Serial

import Data.ByteString.Char8 (pack, unpack) 

import Data.Functor
import Control.Monad
import Control.Applicative
{-import Data.Foldable-}

import Data.List (isSuffixOf)

type PortsPair = (SendPort String, ReceivePort String)

serialSettings = SerialPortSettings CS57600 8 One NoParity NoFlowControl 1

start :: Process PortsPair
start = do
  (inChanSend,inChanReceive) <- newChan :: Process PortsPair
  (outChanSend,outChanReceive) <- newChan :: Process PortsPair

  spawnLocal $ mainProcess (outChanSend, inChanReceive)
  return (inChanSend, outChanReceive)

openDevice :: IO (Maybe SerialPort)
openDevice =  liftIO devicePath >>= oDevice

oDevice :: Maybe String -> IO (Maybe SerialPort)
oDevice Nothing = return Nothing
oDevice (Just path) = do
  serial <- Serial.openSerial path serialSettings
  return $ Just serial
{-oDevice :: Maybe String -> Maybe SerialPort-}
{-oDevice p = p >>= (flip Serial.openSerial serialSettings)-}

mainProcess :: PortsPair -> Process ()
mainProcess channels = do
  file <- liftIO openDevice
  loopProcess file channels

loopProcess :: Maybe SerialPort -> PortsPair -> Process ()
loopProcess Nothing _ = forever $ do
  _ <- expect :: Process String
  liftIO $ errorM rootLoggerName "Arduino Controller can't open device."
loopProcess (Just port) (outChannel,inChannel)  = do
  spawnLocal $ readProcess outChannel port
  forever $ do
    message <- receiveChan inChannel :: Process String
    liftIO $ do
      debugM rootLoggerName ("Arduino Controller receive message: " ++ message )
      Serial.send port (pack message)
      Serial.flush port

readProcess :: SendPort String -> SerialPort-> Process ()
readProcess channel port = forever $ do
  ln <- liftIO $ readLine port
  {-mapM (sendChan channel) ln-}
  sendChan channel ln

readChar :: SerialPort -> IO Char
readChar port = do
  ch <- unpack <$> recv port 1
  case ch of
    [] -> readChar port
    ch -> return $ head $ ch

readLine :: SerialPort -> IO String
readLine port = readLine' port ""

readLine' :: SerialPort -> String -> IO String
readLine' port str = do
  char <- readChar port
  let str' = str ++ [char]
  case isLine str' of
    True -> return $ removeEOL str'
    False -> readLine' port str'
  where isLine = isSuffixOf "\r\n"
        removeEOL = init . init
