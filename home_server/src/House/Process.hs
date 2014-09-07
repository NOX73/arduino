module House.Process where

import qualified Data.Map.Strict as M
import System.Log.Logger (infoM, rootLoggerName)

import Network.Transport.TCP (createTransport, defaultTCPParameters)
import Control.Distributed.Process
import Control.Distributed.Process.Node

import Control.Monad (forever)
import Control.Concurrent (threadDelay)
import Data.Functor

import House.Command

import Arduino.Controller as AC (start)

start :: IO (ProcessId, LocalNode)
start = do
  Right t <- createTransport "127.0.0.1" "10501" defaultTCPParameters
  node <- newLocalNode t initRemoteTable
  pid <- forkProcess node $ mainProcess
  return (pid, node)

mainProcess :: Process ()
mainProcess = do
  (arduinoIn, arduinoOut) <- AC.start

  self <- getSelfPid
  spawnLocal $ arduinoLog arduinoOut

  forever $ do
    liftIO $ infoM rootLoggerName ("Main process expect message ... ")
    command <- expect :: Process Command
    sendCommand command arduinoIn

sendCommand :: Command -> SendPort String -> Process ()
sendCommand TurnOn  = flip sendChan "5,1,4/,4/,1/;;"
sendCommand TurnOff = flip sendChan "5,1,4/,4/,0/;;"
sendCommand command = const $ liftIO $ infoM rootLoggerName ("Main process receive unporcessed command: " ++ show command )

arduinoLog :: ReceivePort String -> Process ()
arduinoLog channel = forever $ do
  line <- receiveChan channel :: Process String
  liftIO $ infoM rootLoggerName ("Arduino Router log: " ++ line )

{-senderProcess pid = forever $ do-}
  {-liftIO $ threadDelay (1*1000000)-}
  {-Just info <- getProcessInfo pid-}
  {-liftIO $ infoM rootLoggerName (show info)-}
  {-send pid (Message "on" )-}

