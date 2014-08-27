module State  where

import Control.Distributed.Process
import Control.Distributed.Process.Node

data State = State ProcessId LocalNode

sendHelloToMainProcess :: State -> IO ()
sendHelloToMainProcess (State pid node) = do
  runProcess node $ do
    send pid "hello"
