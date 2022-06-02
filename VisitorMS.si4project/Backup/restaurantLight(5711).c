#include "controlDevice.h"


int restaurantLightOpen(int pinNum) 
{
	digitalWrite(pinNum, LOW);
}

int restaurantLightClose(int pinNum)
{
	digitalWrite(pinNum, HIGH);
}

int restaurantLightInit(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

int restaurantLightStatus(int status)
{

}


struct controlDevice restaurantLight = {
	.deviceName = "restaurantLight",
	.pinNum = 21,
	.open = restaurantLightOpen,
	.close = restaurantLightClose,
	.deviceInit = restaurantLightInit,
	.changeStatus = restaurantLightStatus,
};

/* 头插法 */
struct controlDevice *addrestaurantLightToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &restaurantLight;
	} else {
		restaurantLight.next = phead;
		phead = &restaurantLight;
	}
}





















