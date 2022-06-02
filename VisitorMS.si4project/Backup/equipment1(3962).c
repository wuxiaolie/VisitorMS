
#include "controlDevice.h"

int equipment1Open(int pinNum) 
{
	digitalWrite(pinNum, LOW);
}

int equipment1Close(int pinNum)
{
	digitalWrite(pinNum, HIGH);
}

int equipment1Init(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

int equipment1Status(int status)
{

}


struct controlDevice equipment1 = {
	.deviceName = "equipment1",
	.pinNum = 22,
	.open = equipment1Open,
	.close = equipment1Close,
	.deviceInit = equipment1Init,
	.changeStatus = equipment1Status,
};

/* 头插法 */
struct controlDevice *addequipment1ToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &equipment1;
	} else {
		equipment1.next = phead;
		phead = &equipment1;
	}
}




















