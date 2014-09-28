package home_server

import (
	"fmt"
	"log"
	"time"

	router "github.com/NOX73/arduino/go_router"
)

const (
	infoUpdateDuration = 10
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

//TODO: timeout
func (c *routerController) SendCommand(cmd router.Command) error {
	c.deviceIn <- cmd
	return nil
}

//TODO: timeout
func (c *routerController) Request(cmd router.Command) (response router.Message, err error) {
	err = c.SendCommand(cmd)
	if err != nil {
		return response, err
	}
	response = <-c.MessageController.ByID(cmd.ID).Out
	return response, nil
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

	log.Println("[ROUTER_CONTROLLER] Opened divice on: ", c.Device.GetPath())

	go c.updateInfo()
}

func (c *routerController) loop() {

	updateInfoTicker := time.Tick(infoUpdateDuration * time.Second)

	for {
		select {
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
		return
	}

	info, ok := resp.Content.(router.MessageInfo)

	if !ok {
		c.Error = err
		return
	}

	log.Println("[ROUTER_CONTROLLER] New Router Info: ", fmt.Sprintf("%+v", info))

	c.Info = info
}
