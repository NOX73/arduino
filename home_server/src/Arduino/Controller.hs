module Arduino.Controller (
  start
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
import System.Log.Logger (errorM, infoM, rootLoggerName)
import Arduino.DevicePath ( devicePath )
import Control.Monad (forever)

import System.IO

start :: Process ProcessId
start = spawnLocal $ mainProcess

mainProcess :: Process ()
mainProcess = do
  path <- liftIO devicePath
  loopProcess $ path

loopProcess :: Maybe String -> Process ()
loopProcess Nothing = forever $ do
  _ <- expect :: Process String
  liftIO $ errorM rootLoggerName "Arduino Controller can't open device."
loopProcess (Just path) = do
  file <- liftIO $ openFile path ReadWriteMode
  forever $ do
    message <- expect :: Process String
    liftIO $ do
      infoM rootLoggerName ("Arduino Controller receive message: " ++ message )
      hPutStrLn file message
      hFlush file




