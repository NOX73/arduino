package home_server

import (
	"sync"

	router "github.com/NOX73/arduino/go_router"
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
			s.Out <- message

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
	m.subscribe(s)
	return s
}

func (m *messageController) Once() *Subscriber {
	s := NewSubscriber(nil, true)
	m.subscribe(s)
	return s
}

func (m *messageController) Filter(trigger TriggerF) *Subscriber {
	s := NewSubscriber(trigger, false)
	m.subscribe(s)
	return s
}

func (m *messageController) FilterOnce(trigger TriggerF) *Subscriber {
	s := NewSubscriber(trigger, true)
	m.subscribe(s)
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

func (m *messageController) unsubscribe(s *Subscriber) {
	m.Lock()
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

	m.Unlock()
}

func (m *messageController) subscribe(s *Subscriber) {
	m.Lock()
	m.subscribers = append(m.subscribers, s)
	m.Unlock()
}
