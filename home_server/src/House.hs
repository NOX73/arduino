module House (
  turnOn,
  turnOff
) where

import Control.Distributed.Process
import Control.Distributed.Process.Node
{-import House.Process ( Command(..) )-}
import State

turnOn :: State -> IO ()
turnOn (State pid node) = do
  runProcess node $ do
    send pid "on"

turnOff :: State -> IO ()
turnOff (State pid node) = do
  runProcess node $ do
    send pid "off"
