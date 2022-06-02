#include "controlDevice.h"


int bathroomLightOpen(int pinNum) 
{
	digitalWrite(pinNum, LOW);
}

int bathroomLightClose(int pinNum)
{
	digitalWrite(pinNum, HIGH);
}

int bathroomLightInit(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

int bathroomLightStatus(int status)
{

}


struct controlDevice bathroomLight = {
	.deviceName = "bathroomLight",
	.pinNum = 22,
	.open = bathroomLightOpen,
	.close = bathroomLightClose,
	.deviceInit = bathroomLightInit,
	.changeStatus = bathroomLightStatus,
};

/* 头插法 */
struct controlDevice *addBathroomLightToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &bathroomLight;
	} else {
		bathroomLight.next = phead;
		phead = &bathroomLight;
	}
}




















