package go_router

import (
	"encoding/json"
	"errors"
)

const (
	MInfo = iota + 1
	MResp
)

var (
	UndefinedContentType = errors.New("Undefined parse content type.")
)

type Message struct {
	ID         int             `json:"id"`
	Type       int             `json:"t"`
	Result     int             `json:"r"`
	ContentRaw json.RawMessage `json:"c"`
	Content    Content
}

type Content interface{}

type MessageInfo struct {
	FreeMemory int       `json:"mem"`
	Radio      RadioInfo `json:"radio"`
}

type RadioInfo struct {
	Level int `json:"lvl"`
}

func (m *Message) unmarshalContent() error {
	if m.ContentRaw == nil {
		return nil
	}

	var err error

	switch m.Type {
	case MInfo:
		mi := MessageInfo{}
		err = json.Unmarshal(m.ContentRaw, &mi)
		m.Content = mi
	default:
		err = UndefinedContentType
	}

	if err == nil {
		m.ContentRaw = nil
	}

	return err
}

func unmarchalMessage(data []byte) (Message, error) {
	m := Message{}
	err := json.Unmarshal(data, &m)

	if err != nil {
		return m, err
	}

	err = (&m).unmarshalContent()

	return m, err
}
