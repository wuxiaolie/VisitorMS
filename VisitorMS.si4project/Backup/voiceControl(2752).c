
#include "inputCommand.h"

int voiceInit(struct inputCommand *voiceDevice, char *ipAdress, char *port)
{
	if ((voiceDevice->fd = serialOpen(voiceDevice->deviceName, 9600)) == -1) {
		printf("Voice module initialization failed - serial port opening failed!\r\n");
		return -1;
	}
	return 1;
}

int voiceGetCommand(struct inputCommand *voiceDevice)
{
	int nread = 0;
	memset(voiceDevice->commandID, '\0',sizeof(voiceDevice->commandID));
	nread = read(voiceDevice->fd, voiceDevice->commandID, sizeof(voiceDevice->commandID));
	return nread;
}

struct inputCommand voiceControl = {
	.commandName = "voice",
	.deviceName = "/dev/ttyAMA0",
	.commandID = {'\0'},
	.initCommand = voiceInit,
	.getCommand = voiceGetCommand,
	.log = {'\0'},
	.next = NULL,
};


/* 头插法 */
struct inputCommand *addvoiceControlToCommand(struct inputCommand *phead)
{
	if (phead == NULL) {
		return &voiceControl;
	} else {
		voiceControl.next = phead;
		phead = &voiceControl;
	}
}


