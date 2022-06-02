#include "controlDevice.h"


int livingroomLightOpen(int pinNum) 
{
	digitalWrite(pinNum, LOW);
}

int livingroomLightClose(int pinNum)
{
	digitalWrite(pinNum, HIGH);
}

int livingroomLightInit(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

int livingroomLightStatus(int status)
{

}


struct controlDevice livingroomLight = {
	.deviceName = "livingroomLight",
	.pinNum = 23,
	.open = livingroomLightOpen,
	.close = livingroomLightClose,
	.deviceInit = livingroomLightInit,
	.changeStatus = livingroomLightStatus,
};

/* 头插法 */
struct controlDevice *addlivingroomLightToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &livingroomLight;
	} else {
		livingroomLight.next = phead;
		phead = &livingroomLight;
	}
}




















