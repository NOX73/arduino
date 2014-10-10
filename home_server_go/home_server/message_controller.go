package home_server

import (
	"log"
	"sync"
	"time"

	//router "github.com/NOX73/arduino/go_router"
	router "../../go_router"
)

type MessageController interface {
	Send(router.Message)

	All() *Subscriber
	Once() *Subscriber
	Filter(TriggerF) *Subscriber
	FilterOnce(TriggerF) *Subscriber

	Enough(*Subscriber)

	ByID(id int) *Subscriber
}

func NewMessageController() MessageController {
	return &messageController{}
}

type messageController struct {
	sync.Mutex
	subscribers []*Subscriber
}

func (m *messageController) Send(message router.Message) {
	m.Lock()
	var toRemove []*Subscriber
	subs := m.subscribers

	for _, s := range subs {
		if s.Triggered(message) {

			//TODO: timeout

			timeout := time.After(timeoutTime * time.Millisecond)

			select {
			case s.Out <- message:
			case <-timeout:
				log.Println("[MessageController] Warning: Timeout to deliver message.")
			}

			if s.Once {
				toRemove = append(toRemove, s)
			}

		}
	}

	for _, s := range toRemove {
		m.unsubscribe(s)
	}

	m.Unlock()
}

func (m *messageController) All() *Subscriber {
	s := NewSubscriber(nil, false)
	m.Subscribe(s)
	return s
}

func (m *messageController) Once() *Subscriber {
	s := NewSubscriber(nil, true)
	m.Subscribe(s)
	return s
}

func (m *messageController) Filter(trigger TriggerF) *Subscriber {
	s := NewSubscriber(trigger, false)
	m.Subscribe(s)
	return s
}

func (m *messageController) FilterOnce(trigger TriggerF) *Subscriber {
	s := NewSubscriber(trigger, true)
	m.Subscribe(s)
	return s
}

func (m *messageController) ByID(id int) *Subscriber {
	return m.FilterOnce(func(m router.Message) bool {
		return m.ID == id
	})
}

func (m *messageController) Enough(s *Subscriber) {
	m.unsubscribe(s)
}

func (m *messageController) Subscribe(s *Subscriber) {
	m.Lock()
	m.subscribe(s)
	m.Unlock()
}

func (m *messageController) Unsubscribe(s *Subscriber) {
	m.Lock()
	m.unsubscribe(s)
	m.Unlock()
}

func (m *messageController) unsubscribe(s *Subscriber) {
	subs := m.subscribers

	for i, item := range subs {
		if item == s {
			copy(subs[i:], subs[i+1:])
			subs[len(subs)-1] = nil
			subs = subs[:len(subs)-1]

			m.subscribers = subs

			return
		}
	}

}

func (m *messageController) subscribe(s *Subscriber) {
	m.subscribers = append(m.subscribers, s)
}
