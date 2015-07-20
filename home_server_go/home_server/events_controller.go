package home_server

import (
	"errors"
	"log"

	router "../go_router"
)

var (
	cantListenEventsError = errors.New("[listenEvents] listen command failed.")
)

func runEventsController(out chan<- router.Command, stream MessageController) {
	err := listenEvents(out, stream)
	if err != nil {
		log.Println("[EventController] Error on start: ", err)
		return
	}

	sub := stream.Filter(func(m router.Message) bool {
		return m.Type == router.MEvent
	})
	defer stream.Enough(sub)

	for {
		select {
		case event := <-sub.Out:
			log.Println("[EventController] Event received:", event)
		}
	}

	log.Println("[EventController] Finished")
}

func listenEvents(out chan<- router.Command, stream MessageController) error {
	cmd := router.NewCommandListenEvents()
	resp, err := sendRequest(cmd, out, stream, timeoutTime)

	if err != nil {
		return err
	}

	if resp.Result != 1 {
		return cantListenEventsError
	}

	return nil
}
