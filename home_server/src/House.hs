module House (
  turnOn,
  turnOff,
  start
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
import House.Command ( Command(..) )
import State
import House.Process (start)

turnOn :: State -> IO ()
turnOn (State pid node) = do
  runProcess node $ do
    send pid TurnOn

turnOff :: State -> IO ()
turnOff (State pid node) = do
  runProcess node $ do
    send pid TurnOff
