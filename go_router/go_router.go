package go_router

import (
  "github.com/tarm/goserial"
  "io"
  "encoding/binary"
)

const (
  SerialBaud = 115200
)

type Router interface {
  Read() ([]byte, error)
  Write([]byte) error
}

func OpenDevice(path string) (Router, error) {
  c := &serial.Config{Name: path, Baud: SerialBaud}
  s, err := serial.OpenPort(c)

  if(err != nil) {
    return nil, err
  }

  return &router{s}, nil
}

type router struct {
  serial io.ReadWriteCloser
}

func (r *router) Read () ([]byte, error) {
  var err error;
  var length int32;

  err = binary.Read(r.serial, binary.LittleEndian, &length);
  if err != nil {return nil, err}

  pack := make([]byte, length);

  err = binary.Read(r.serial, binary.LittleEndian, pack);
  if err != nil {return nil, err}

  return pack, nil;
}

func (r *router) Write (buff []byte) error {
  var err error;
  var length int32 = int32(len(buff));

  err = binary.Write(r.serial, binary.LittleEndian, length);
  if err != nil {return err}

  err = binary.Write(r.serial, binary.LittleEndian, buff);
  if err != nil {return err}

  return nil;
}
