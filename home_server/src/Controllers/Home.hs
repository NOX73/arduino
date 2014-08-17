module Controllers.Home ( index ) where

import Web.Scotty
import Arduino.DevicePath as D
{-import System.Log.Logger (infoM, rootLoggerName)-}
import Data.String (fromString)
import Control.Monad.IO.Class

index :: ActionM ()
index  = do
  path <- liftIO D.devicePath
  {-liftIO $ infoM rootLoggerName ("GET /. Path = " ++ path)-}
  html $ fromString path
