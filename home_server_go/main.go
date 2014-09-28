package main

import (
	"log"
	"time"

	"./home_server"
)

func main() {

	_, err := home_server.NewRouterController()

	if err != nil {
		log.Fatal(err)
	}

	time.Sleep(60 * time.Second)

	log.Println("Done.")
}
