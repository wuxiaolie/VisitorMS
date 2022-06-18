
#include "inputCommand.h"

int usartInit(struct inputCommand *usartDevice, char *ipAdress, char *port)
{
	if ((usartDevice->fd = serialOpen(usartDevice->deviceName, 9600)) == -1) {
		printf("usart module initialization failed - serial port opening failed!\r\n");
		return -1;
	}
	return 1;
}

int usartGetCommand(struct inputCommand *usartDevice)
{
	int nread = 0;
	memset(usartDevice->commandID, '\0',sizeof(usartDevice->commandID));
	nread = read(usartDevice->fd, usartDevice->commandID, sizeof(usartDevice->commandID));
	return nread;
}

struct inputCommand usartControl = {
	.commandName = "usart",
	.deviceName = "/dev/ttyAMA0",
	.commandID = {'\0'},
	.initCommand = usartInit,
	.getCommand = usartGetCommand,
	.log = {'\0'},
	.next = NULL,
};


/* 头插法 */
struct inputCommand *addusartControlToCommand(struct inputCommand *phead)
{
	if (phead == NULL) {
		return &usartControl;
	} else {
		usartControl.next = phead;
		phead = &usartControl;
	}
}



