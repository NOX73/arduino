{-# LANGUAGE OverloadedStrings #-}
module Controllers.Home ( index ) where

import Web.Scotty
import Arduino.DevicePath (devicePath)
import Data.String (fromString)
import Control.Monad.IO.Class (liftIO)
import Data.Maybe (fromMaybe)

import State
import System.Log.Logger (infoM, rootLoggerName)
import Control.Distributed.Process

import House (turnOff, turnOn)

index :: State -> ActionM ()
index state = do
  p <- param "pos"
  liftIO $ sendCommand $ fromString p
  body <- liftIO getBody
  html $ fromString $ body

  where sendCommand "on" = turnOn state
        sendCommand "off" = turnOff state

        getBody = do
          path <- devicePath
          return $ fromMaybe "NO" path



