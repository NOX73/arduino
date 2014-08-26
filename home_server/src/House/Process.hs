module House.Process where

import qualified Data.Map.Strict as M
import System.Log.Logger (infoM, rootLoggerName)

import Network.Transport.TCP (createTransport, defaultTCPParameters)
import Control.Distributed.Process
import Control.Distributed.Process.Node

import Control.Monad (forever)
import Control.Concurrent (threadDelay)
import Data.Functor
{-import Control.Monad-}

mainDelay = 1 * 1000000
childDelay = 1 * 1000000

start :: IO ProcessId
start = do
  Right t <- createTransport "127.0.0.1" "10501" defaultTCPParameters
  node <- newLocalNode t initRemoteTable
  forkProcess node $ mainProcess

mainProcess :: Process ()
mainProcess = do
  childPid <- spawnLocal $ childProcess
  forever $ do
    let message = "hello"
    send childPid message
    liftIO $ do infoM rootLoggerName ("Main process sended message: " ++ message )
                threadDelay mainDelay

childProcess :: Process ()
childProcess = forever $ do

  message <- expect :: Process String

  liftIO $ do infoM rootLoggerName ("Child received message: " ++ message)
              threadDelay childDelay

