module Arduino.DevicePath (
  devicePath
) where

import System.Directory (getDirectoryContents)
import Data.List (isInfixOf)
import Control.Monad (filterM)
import Data.Functor

type DevicePath = String

isTTY :: DevicePath -> Bool
isTTY = isInfixOf "tty"

isUSB :: DevicePath -> Bool
isUSB = isInfixOf "Blu"

isDevice :: DevicePath -> Bool
isDevice path = isTTY path && isUSB path

allDevicePaths :: IO [DevicePath]
allDevicePaths = getDirectoryContents "/dev/"

devicePaths :: IO [DevicePath]
devicePaths = filter isDevice <$> allDevicePaths

devicePath :: IO DevicePath
devicePath = head <$> devicePaths
