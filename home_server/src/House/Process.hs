{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE DeriveGeneric #-}

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

import Data.Binary
import GHC.Generics (Generic)
import Data.Typeable

data Command = TurnOn | TurnOff | Message String
  deriving (Show, Eq, Generic, Typeable)

instance Binary Command

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
    {-command <- expect :: Process Command-}
    command <- expect :: Process String
    processCommand arduinoController command
    {-liftIO $ infoM rootLoggerName ("Main process receive message: " ++ receiveMessage )-}

    {-send arduinoController ("5,1,4/,4/,0/;;" :: String)-}

childProcess :: Process ()
childProcess = forever $ do
  message <- expect :: Process String
  liftIO $ do infoM rootLoggerName ("Child received message: " ++ message)


processCommand :: ProcessId -> String -> Process ()
processCommand arduino "on" = send arduino ("5,1,4/,4/,1/;;" :: String)
processCommand arduino "off" = send arduino ("5,1,4/,4/,0/;;" :: String)
processCommand arduino command = liftIO $ infoM rootLoggerName ("Main process receive command: " ++ command )

{-processCommand :: ProcessId -> Command -> Process ()-}
{-processCommand arduino TurnOn = send arduino ("5,1,4/,4/,1/;;" :: String)-}
{-processCommand arduino TurnOff = send arduino ("5,1,4/,4/,0/;;" :: String)-}
{-processCommand arduino command = liftIO $ infoM rootLoggerName ("Main process receive command: " ++ show command )-}
 

