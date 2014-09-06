module State  where

import Control.Distributed.Process
import Control.Distributed.Process.Node

data State = State ProcessId LocalNode
