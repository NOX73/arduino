package go_router

import (
	"encoding/json"
	"sync"
)

type Command interface{}

type command struct {
	ID   int `json:"id"`
	Type int `json:"t"`
}

const (
	CInfo = iota + 1
	CListenEvents
)

var CID int = 1
var CIDMutex = sync.Mutex{}

func nextCID() int {
	CIDMutex.Lock()
	var cid = CID
	CID++
	CIDMutex.Unlock()

	return cid
}

func NewCommand(cType int) Command {
	return command{nextCID(), cType}
}

func NewCommandInfo() Command {
	return NewCommand(CInfo)
}

func NewCommandListenEvents() Command {
	return NewCommand(CListenEvents)
}

func marshalCommand(cmd Command) ([]byte, error) {
	data, err := json.Marshal(cmd)
	return data, err
}
