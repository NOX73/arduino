module Arduino.DevicePath (
  devicePath
) where

import System.Directory (getDirectoryContents)
import Data.List (isInfixOf)
import Data.Functor

type DevicePath = String

isTTY :: DevicePath -> Bool
isTTY = isInfixOf "tty"

isUSB :: DevicePath -> Bool
isUSB = isInfixOf "USB"

isDevice :: DevicePath -> Bool
isDevice path = isTTY path && isUSB path

allDevicePaths :: IO [DevicePath]
allDevicePaths = getDirectoryContents "/dev/"

devicePaths :: IO [DevicePath]
devicePaths = filter isDevice <$> allDevicePaths

getFirst :: [DevicePath] -> Maybe DevicePath
getFirst [] = Nothing
getFirst (h:_) = Just h

devicePath :: IO (Maybe DevicePath)
devicePath =  getFirst <$> devicePaths
