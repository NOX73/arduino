{-# LANGUAGE OverloadedStrings #-}
import Web.Scotty
import Arduino
import Data.String

main = do

  path <- Arduino.devicePath

  scotty 3000 $ do
    get "/" $ do
      html $ (fromString path)
