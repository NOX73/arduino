init: sandbox_init deps config

build:
	cabal build home_server

run:
	cabal run home_server

deps:
	cabal update && \
	cabal install --only-dependencies

sandbox_init:
	cabal sandbox init

config:
	cabal configure

