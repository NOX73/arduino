package home_server

import (
	//router "github.com/NOX73/arduino/go_router"
	router "../go_router"
)

type TriggerF func(router.Message) bool

type Subscriber struct {
	Out     chan router.Message
	Trigger TriggerF
	Once    bool
	On      bool
}

func NewSubscriber(trigger TriggerF, once bool) *Subscriber {
	out := make(chan router.Message)
	return &Subscriber{
		Out:     out,
		Trigger: trigger,
		Once:    once,
		On:      true,
	}
}

func (s *Subscriber) Triggered(message router.Message) bool {
	return s.Trigger == nil || s.Trigger(message)
}
