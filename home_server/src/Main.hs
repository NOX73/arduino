{-# LANGUAGE OverloadedStrings #-}
import Web.Scotty
import Web.Controllers.Home as HomeController
import Network.Wai.Middleware.RequestLogger (logStdoutDev)
import Network.Wai.Middleware.Static (addBase, noDots, staticPolicy, (>->))
import System.Log.Logger
import House (start)
import Control.Monad.IO.Class (liftIO)

import State
import Control.Distributed.Process

main = do

  (pid, node) <- House.start
  updateGlobalLogger rootLoggerName (setLevel DEBUG)

  state <- return $ State pid node

  scotty 3000 $ do

    {-middleware logStdoutDev-}
    middleware $ staticPolicy (noDots >-> addBase "static/")

    get "/" $ HomeController.index state
