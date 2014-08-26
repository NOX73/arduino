module House.Process where

import qualified Data.Map.Strict as M
import System.Log.Logger (infoM, rootLoggerName)

import Network.Transport.TCP (createTransport, defaultTCPParameters)
import Control.Distributed.Process
import Control.Distributed.Process.Node

import Control.Monad (forever)
import Control.Concurrent (threadDelay)
import Data.Functor

start :: IO ProcessId
start = do
  Right t <- createTransport "127.0.0.1" "10501" defaultTCPParameters
  node <- newLocalNode t initRemoteTable
  forkProcess node $ do
    spawnLocal $ forever $ processLoop
    return ()

processLoop :: Process ()
processLoop = liftIO $ do
  infoM rootLoggerName "Process log" 
  threadDelay (10*1000000)

