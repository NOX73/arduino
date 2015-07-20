package home_server

import (
	"errors"
	"fmt"
	"log"
	"reflect"
	"time"

	//router "github.com/NOX73/arduino/go_router"
	router "../go_router"
)

const (
	infoUpdateDuration   = 10 * time.Second
	timeoutTime          = 1000 * time.Millisecond
	commandsChanCapacity = 5
)

var (
	timeoutError = errors.New("[RouterController] Error: Timeout error")
)

type RouterController interface {
	GetInfo() router.MessageInfo
	GetError() error
	IsConnected() bool

	SendCommand(router.Command) error
	Request(cmd router.Command) (response router.Message, err error)
}

func NewRouterController() (RouterController, error) {
	device, err := router.GetDevice()

	if err != nil {
		return nil, err
	}

	controller := &routerController{
		Device:            device,
		MessageController: NewMessageController(),
		connected:         false,
		CommandsChan:      make(chan router.Command, commandsChanCapacity),
	}

	controller.init()

	return controller, nil
}

type routerController struct {
	Device router.Router
	Error  error
	Info   router.MessageInfo

	connected bool

	deviceIn  chan<- router.Command
	deviceOut <-chan router.Message

	MessageController MessageController

	CommandsChan chan router.Command
}

func (c *routerController) GetInfo() router.MessageInfo {
	return c.Info
}

func (c *routerController) GetError() error {
	return c.Error
}

func (c *routerController) IsConnected() bool {
	return c.connected
}

func (c *routerController) SendCommand(cmd router.Command) error {
	return sendCommand(cmd, c.deviceIn, timeoutTime)
}

func (c *routerController) Request(cmd router.Command) (response router.Message, err error) {
	return sendRequest(cmd, c.deviceIn, c.MessageController, timeoutTime)
}

func (c *routerController) init() {
	c.setup()
	go c.loop()
}

func (c *routerController) setup() {
	in, out, _ := c.Device.StartStream()

	c.deviceIn = in
	c.deviceOut = out

	c.connected = true

	log.Println("[RouterController] Opened divice on: ", c.Device.GetPath())

	go c.updateInfo()
	go runEventsController(c.CommandsChan, c.MessageController)
}

func (c *routerController) logAllMessages() {
	all := c.MessageController.All().Out

	for {
		message := <-all
		log.Println("[RouterController] New Message: ", fmt.Sprintf("%+v", message))
	}
}

func (c *routerController) loop() {

	updateInfoTicker := time.Tick(infoUpdateDuration)

	for {
		select {
		case command := <-c.CommandsChan:
			err := c.SendCommand(command)
			if err != nil {
				log.Println("[RouterController] Error on SendCommand: ", err)
			}
		case <-updateInfoTicker:
			go c.updateInfo()
		case m := <-c.deviceOut:
			c.MessageController.Send(m)
		}
	}

}

func (c *routerController) updateInfo() {
	cmd := router.NewCommandInfo()
	resp, err := c.Request(cmd)

	if err != nil {
		c.Error = err
		log.Println("[RouterController] updateInfo ")
		return
	}

	info, ok := resp.Content.(router.MessageInfo)

	if !ok {
		log.Println("[RouterController] updateInfo type cast error. Real type is ", reflect.TypeOf(resp.Content))
		return
	}

	log.Println("[RouterController] New Router Info: ", fmt.Sprintf("%+v", info))

	c.Info = info
}
