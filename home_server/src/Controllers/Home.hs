module Controllers.Home ( index ) where

import Web.Scotty
import Arduino.DevicePath as D
{-import System.Log.Logger (infoM, rootLoggerName)-}
import Data.String (fromString)
import Control.Monad.IO.Class (liftIO)
import Data.Maybe (fromMaybe)

index :: ActionM ()
index  = do
  path <- liftIO D.devicePath
  html $ fromString $ fromMaybe "NO" path
