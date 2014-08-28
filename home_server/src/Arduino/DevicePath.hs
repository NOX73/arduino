module Arduino.DevicePath (
  devicePath
) where

import System.Directory (getDirectoryContents)
import Data.List (isInfixOf)
import Data.Functor

type DevicePath = String

directory = "/dev/"

isTTY :: DevicePath -> Bool
isTTY = isInfixOf "tty"

isUSB :: DevicePath -> Bool
isUSB = isInfixOf "USB"

isDevice :: DevicePath -> Bool
isDevice path = isTTY path && isUSB path

allDevicePaths :: IO [DevicePath]
allDevicePaths = getDirectoryContents directory

devicePaths :: IO [DevicePath]
devicePaths = filter isDevice <$> allDevicePaths

getFirst :: [DevicePath] -> Maybe DevicePath
getFirst [] = Nothing
getFirst (h:_) = Just h

fullPath :: Maybe DevicePath -> Maybe DevicePath
fullPath Nothing = Nothing
fullPath (Just path) = Just (directory ++ path)

devicePath :: IO (Maybe DevicePath)
devicePath =  fullPath <$> getFirst <$> devicePaths
