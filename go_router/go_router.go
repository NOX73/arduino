package go_router

import (
	"errors"
	"io/ioutil"
	"strings"
	"time"

	"github.com/tarm/goserial"
)

const (
	SerialBaud = 115200

	maxSetupLength = 20
	minSetupLength = 5
	waitForDevice  = 3
)

var (
	ArduinoNotFound = errors.New("Arduino device not found.")
)

type Router interface {
	Read() ([]byte, error)
	Write([]byte) error
	StartStream() (in chan<- Command, out <-chan Message, kill chan<- interface{})
	GetPath() string
}

func GetDevice() (Router, error) {
	path, err := findArduino()
	if err != nil {
		return nil, err
	}

	r, err := OpenDevice(path)

	return r, err
}

func findArduino() (string, error) {
	contents, _ := ioutil.ReadDir("/dev")

	for _, f := range contents {
		if strings.Contains(f.Name(), "tty.usbserial") ||
			strings.Contains(f.Name(), "ttyUSB") {
			return "/dev/" + f.Name(), nil
		}
	}
	return "", ArduinoNotFound
}

func OpenDevice(path string) (Router, error) {
	c := &serial.Config{Name: path, Baud: SerialBaud}
	s, err := serial.OpenPort(c)

	if err != nil {
		return nil, err
	}

	r := &router{
		Path:   path,
		serial: s,
	}

	time.Sleep(waitForDevice * time.Second)

	err = r.Setup()
	return r, err
}
