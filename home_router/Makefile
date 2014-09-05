ARDUINO = /Applications/Arduino.app/Contents/MacOS/JavaApplicationStub
INO = $(shell pwd)/home_router.ino
PORT = /dev/tty.usbserial*
BOARD = arduino:avr:nano
SERIAL_BAUD = 57600

all: upload screen

upload:
	$(ARDUINO) --board $(BOARD) --port $(PORT) --upload $(INO)

build:
	$(ARDUINO) --board $(BOARD) --port $(PORT) --verify $(INO)

screen:
	screen $(PORT) $(SERIAL_BAUD)

