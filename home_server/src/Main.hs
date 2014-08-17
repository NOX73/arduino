{-# LANGUAGE OverloadedStrings #-}
import Web.Scotty
import Controllers.Home as H
import Network.Wai.Middleware.RequestLogger (logStdoutDev)
import Network.Wai.Middleware.Static (addBase, noDots, staticPolicy, (>->))
import System.Log.Logger 

main = do

  updateGlobalLogger rootLoggerName (setLevel DEBUG)

  scotty 3000 $ do

    middleware logStdoutDev
    middleware $ staticPolicy (noDots >-> addBase "static/")

    get "/" $ H.index
