module House.Process where

import qualified Data.Map.Strict as M
import System.Log.Logger (infoM, rootLoggerName)

import Network.Transport.TCP (createTransport, defaultTCPParameters)
import Control.Distributed.Process
import Control.Distributed.Process.Node

import Control.Monad (forever)
import Control.Concurrent (threadDelay)
import Data.Functor

import Arduino.Controller as AC (start)

start :: IO (ProcessId, LocalNode)
start = do
  Right t <- createTransport "127.0.0.1" "10501" defaultTCPParameters
  node <- newLocalNode t initRemoteTable
  pid <- forkProcess node $ mainProcess
  return (pid, node)

mainProcess :: Process ()
mainProcess = do

  arduinoController <- AC.start

  forever $ do

    liftIO $ infoM rootLoggerName ("Main process expect message ... ")
    receiveMessage <- expect :: Process String
    liftIO $ infoM rootLoggerName ("Main process receive message: " ++ receiveMessage )

    send arduinoController ("5,1,4/,4/,0/;;" :: String)

childProcess :: Process ()
childProcess = forever $ do
  message <- expect :: Process String
  liftIO $ do infoM rootLoggerName ("Child received message: " ++ message)

