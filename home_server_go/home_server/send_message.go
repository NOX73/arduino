package home_server

import (
	"errors"
	"time"

	router "../go_router"
)

var (
	sendCommandTimeoutError = errors.New("[sendCommand] Error: Timeout error")
	sendRequestTimeoutError = errors.New("[sendRequest] Error: Timeout error")
)

func sendCommand(cmd router.Command, ch chan<- router.Command, timeoutTime time.Duration) error {
	var timeout <-chan time.Time

	if timeoutTime > 0 {
		timeout = time.After(timeoutTime)
	}

	select {
	case ch <- cmd:
	case <-timeout:
		return sendCommandTimeoutError
	}

	return nil
}

func sendRequest(cmd router.Command, in chan<- router.Command, stream MessageController, timeoutTime time.Duration) (response router.Message, err error) {
	err = sendCommand(cmd, in, timeoutTime)
	if err != nil {
		return response, err
	}

	var timeout <-chan time.Time

	if timeoutTime > 0 {
		timeout = time.After(timeoutTime)
	}

	select {
	case response = <-stream.ByID(cmd.ID).Out:
	case <-timeout:
		return response, sendRequestTimeoutError
	}

	return response, nil

}
