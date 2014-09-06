module House (
  turnOn,
  turnOff
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
import House.Command ( Command(..) )
import State

turnOn :: State -> IO ()
turnOn (State pid node) = do
  runProcess node $ do
    send pid TurnOn

turnOff :: State -> IO ()
turnOff (State pid node) = do
  runProcess node $ do
    send pid TurnOff
