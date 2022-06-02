
#include "controlDevice.h"

int equipment2Open(int pinNum) 
{
	digitalWrite(pinNum, LOW);
	printw("-----------------------Equipment2 open seccess!----------------------\n");
}

int equipment2Close(int pinNum)
{
	digitalWrite(pinNum, HIGH);
	printw("-----------------------Equipment2 close seccess!---------------------\n");
}

int equipment2Init(int pinNum)
{
	pinMode(pinNum, OUTPUT);
	digitalWrite(pinNum, HIGH);
}

int equipment2Status(int pinNum)
{
	if(digitalRead(pinNum) == 1) {
		printw("-----------------------Equipment2 is open!-----------------------\n");
	} else {
		printw("-----------------------Equipment2 is close!----------------------\n");
	}
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





















