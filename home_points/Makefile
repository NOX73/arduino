ARDUINO = /Applications/Arduino.app/Contents/MacOS/JavaApplicationStub
ARDUINO_REMOTE = arduino
INO = $(shell pwd)/home_points.ino
SERIAL = /dev/tty.usbserial-*
SERIAL_2 = /dev/tty.usbserial
SERIAL_REMOTE = $$HOME/dev/tty.remote
SERIAL_REMOTE_SERVER = /dev/ttyUSB0
BOARD = arduino:avr:nano
SERIAL_BAUD = 115200

REMOTE_TTY_PORT:=$(shell bash -c 'echo $$((RANDOM%65000+20000))')
REMOTE_TTY_HOST=192.168.1.2

REMOTE_SSH_DIR = ~/Arduino/home_points
INO_REMOTE = $(REMOTE_SSH_DIR)/home_points.ino

all: upload screen

upload:
	$(ARDUINO) --board $(BOARD) --port $(SERIAL) --upload $(INO)
upload_2:
	$(ARDUINO) --board $(BOARD) --port $(SERIAL_2) --upload $(INO)

build:
	$(ARDUINO) --board $(BOARD) --port $(SERIAL) --verify $(INO)

screen:
	screen $(SERIAL) $(SERIAL_BAUD)
screen_2:
	screen $(SERIAL_2) $(SERIAL_BAUD)

screen_remote:
	make start_remote_tty > /dev/null 2>&1 &
	sleep 10
	screen $(SERIAL_REMOTE) $(SERIAL_BAUD)

start_remote_tty: start_remote_tty_server wait_remote_tty_server start_remote_tty_client
wait_remote_tty_server:
	sleep 2
start_remote_tty_server:
	ssh $(REMOTE_TTY_HOST) -f "killall socat; socat TCP-LISTEN:$(REMOTE_TTY_PORT) $(SERIAL_REMOTE_SERVER),nonblock,raw,echo=0"
start_remote_tty_client:
	socat -d -d -d pty,link=$(SERIAL_REMOTE),echo=0,crnl tcp:$(REMOTE_TTY_HOST):$(REMOTE_TTY_PORT)

upload_remote_net: start_remote_tty_server
	$(ARDUINO) --board $(BOARD) --port net:$(REMOTE_TTY_HOST):$(REMOTE_TTY_PORT) --upload $(INO)

upload_remote_serial:
	$(ARDUINO) --verbose --board $(BOARD) --port $(SERIAL_REMOTE) --upload $(INO)

upload_remote_ssh:
	ssh $(REMOTE_TTY_HOST) "mkdir $(REMOTE_SSH_DIR)"; \
	scp -r ./*.ino 192.168.1.2:$(REMOTE_SSH_DIR) && \
	ssh -X $(REMOTE_TTY_HOST) "cd $(REMOTE_SSH_DIR) && $(ARDUINO_REMOTE) --board $(BOARD) --port $(SERIAL_REMOTE_SERVER) --upload $(INO_REMOTE)";
	ssh $(REMOTE_TTY_HOST) "rm -rf $(REMOTE_SSH_DIR)";

