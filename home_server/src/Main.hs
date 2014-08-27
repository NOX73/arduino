{-# LANGUAGE OverloadedStrings #-}
import Web.Scotty
import Controllers.Home as H
import Network.Wai.Middleware.RequestLogger (logStdoutDev)
import Network.Wai.Middleware.Static (addBase, noDots, staticPolicy, (>->))
import System.Log.Logger
import House.Process as P
import Control.Monad.IO.Class (liftIO)

import State
import Control.Distributed.Process

main = do

  (pid, node) <- P.start
  updateGlobalLogger rootLoggerName (setLevel DEBUG)

  state <- return $ State pid node

  scotty 3000 $ do

    middleware logStdoutDev
    middleware $ staticPolicy (noDots >-> addBase "static/")

    get "/" $ H.index state
