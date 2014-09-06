{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE DeriveGeneric #-}

module House.Command where

import Data.Binary
import Data.Typeable
import GHC.Generics (Generic)

data Command = TurnOn | TurnOff | Message String
  deriving (Show, Eq, Typeable, Generic)

instance Binary Command


