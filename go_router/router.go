package go_router

import (
	"encoding/binary"
	"errors"
	"io"
	"log"
	"math/rand"
)

var (
	SetupLengthError = errors.New("Device setup has failured. Lengths don't match.")
	SetupPackError   = errors.New("Device setup has failured. Packs's contents don't match.")
)

type router struct {
	serial io.ReadWriteCloser
}

func (r *router) StartStream() (chan<- Command, <-chan Message, chan<- interface{}) {
	in := make(chan Command)
	out := make(chan Message)
	kill := make(chan interface{})

	go func() {
		for {
			data, err := r.Read()
			if err != nil {
				log.Fatal(err)
			}

			msg, err := unmarchalMessage(data)
			if err != nil {
				log.Fatal(err)
			}

			out <- msg
		}
	}()

	go func() {
		for {
			cmd := <-in

			data, err := marshalCommand(cmd)
			if err != nil {
				log.Fatal(err)
			}

			r.Write(data)
		}
	}()

	return in, out, kill
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
