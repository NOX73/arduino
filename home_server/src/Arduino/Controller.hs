module Arduino.Controller (
  start
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
import System.Log.Logger (errorM, infoM, rootLoggerName)
import Arduino.DevicePath ( devicePath )
import Control.Monad (forever)

start :: Process ProcessId
start = spawnLocal $ mainProcess

mainProcess :: Process ()
mainProcess = do
  path <- liftIO devicePath
  loopProcess path

loopProcess :: Maybe String -> Process ()
loopProcess Nothing = do
  liftIO $ errorM rootLoggerName "Arduino Controller can't open device."
loopProcess (Just path) = forever $ do
  message <- expect :: Process String
  liftIO $ infoM rootLoggerName ("Arduino Controller receive message: " ++ message )
  liftIO $ infoM rootLoggerName (path)


