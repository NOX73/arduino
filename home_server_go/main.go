package main

import (
	"log"

	router "github.com/NOX73/arduino/go_router"
)

func main() {

	var err error

	device, err := router.GetDevice()

	if err != nil {
		log.Fatal(err)
	}

	log.Println("Device opened.")

	err = device.Write([]byte("{\"id\":4,\"cmd\":1}"))

	if err != nil {
		log.Fatal(err)
	}

	for {
		a, err := device.Read()

		if err != nil {
			log.Fatal(err)
		}

		log.Println(string(a))
	}

}
