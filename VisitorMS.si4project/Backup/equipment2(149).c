
#include "controlDevice.h"

int equipment2Open(int pinNum) 
{
	digitalWrite(pinNum, LOW);
}

int equipment2Close(int pinNum)
{
	digitalWrite(pinNum, HIGH);
}

int equipment2Init(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

int equipment2Status(int pinNum)
{
	return digitalRead(pinNum);
}


struct controlDevice equipment2 = {
	.deviceName = "equipment2",
	.pinNum = 21,
	.open = equipment2Open,
	.close = equipment2Close,
	.deviceInit = equipment2Init,
	.changeStatus = equipment2Status,
};

/* 头插法 */
struct controlDevice *addequipment2ToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &equipment2;
	} else {
		equipment2.next = phead;
		phead = &equipment2;
	}
}





















