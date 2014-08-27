module Controllers.Home ( index ) where

import Web.Scotty
import Arduino.DevicePath (devicePath)
import Data.String (fromString)
import Control.Monad.IO.Class (liftIO)
import Data.Maybe (fromMaybe)

import State
import System.Log.Logger (infoM, rootLoggerName)
import Control.Distributed.Process

index :: State -> ActionM ()
index state = do
  sendHello
  body <- liftIO getBody
  html $ fromString $ body

  where sendHello = do 
          liftIO $ infoM rootLoggerName "sending..."
          liftIO $ sendHelloToMainProcess state

        getBody = do
          path <- devicePath
          return $ fromMaybe "NO" path
