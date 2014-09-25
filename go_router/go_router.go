package go_router

import (
	"encoding/binary"
	"errors"
	"io"
	"io/ioutil"
	"math/rand"
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
	SetupLengthError = errors.New("Device setup has failured. Lengths don't match.")
	SetupPackError   = errors.New("Device setup has failured. Packs's contents don't match.")
	ArduinoNotFound  = errors.New("Arduino device not found.")
)

type Router interface {
	Read() ([]byte, error)
	Write([]byte) error
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

	r := &router{s}

	time.Sleep(waitForDevice * time.Second)

	err = r.Setup()
	return r, err
}

type router struct {
	serial io.ReadWriteCloser
}

func (r *router) Read() ([]byte, error) {
	var err error
	var length uint32

	err = binary.Read(r.serial, binary.LittleEndian, &length)
	if err != nil {
		return nil, err
	}

	pack := make([]byte, length)

	err = binary.Read(r.serial, binary.LittleEndian, pack)
	if err != nil {
		return nil, err
	}

	return pack, nil
}

func (r *router) Write(buff []byte) error {
	var err error
	var length uint32 = uint32(len(buff))

	err = binary.Write(r.serial, binary.LittleEndian, length)
	if err != nil {
		return err
	}

	err = binary.Write(r.serial, binary.LittleEndian, buff)
	if err != nil {
		return err
	}

	return nil
}

func (r *router) Setup() error {
	var err error
	length := minSetupLength + rand.Intn(maxSetupLength-minSetupLength)

	pack := make([]byte, length)

	for i := 0; i < length; i++ {
		pack[i] = byte(rand.Intn(256))
	}

	err = r.Write(pack)
	if err != nil {
		return err
	}

	reply, err := r.Read()
	if err != nil {
		return err
	}

	if len(reply) != len(pack) {
		return SetupLengthError
	}

	for i := 0; i < length; i++ {
		if pack[i] != reply[i] {
			return SetupPackError
		}
	}

	return nil
}
