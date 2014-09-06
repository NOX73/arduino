.PHONY: all init build run deps vagrant config repl

all: build run

init: sandbox_init deps config

build:
	cabal build home_server

run:
	cabal run home_server

deps:
	cabal update && \
	cabal install --only-dependencies

deps_upgrade:
	cabal update && \
	cabal install --upgrade-dependencies && \
	cabal configure

sandbox_init:
	cabal sandbox init

config:
	cabal configure

repl:
	cabal repl



vagrant_init: vagrant_init_ vagrant_reinit
vagrant_init_:
	cd vagrant && \
		vagrant up && \
		vagrant ssh -c 'mkdir home_server'

vagrant_ssh:
	cd vagrant && \
		vagrant up && \
		vagrant ssh

vagrant_halt:
	cd vagrant && vagrant halt

build_linux:
	cd vagrant && vagrant up && vagrant provision

vagrant_reinit:
	cd vagrant && \
		vagrant up && \
		vagrant ssh -c 'cd home_server && rm -rf ./* && cp -r /arduino/* ./ && rm -rf .cabal-sandbox && ~/.cabal/bin/cabal sandbox init && ~/.cabal/bin/cabal install && ~/.cabal/bin/cabal configure'

deploy: build_linux
	scp dist/build/home_server/home_server.linux 192.168.1.2:~/
