
#include "controlDevice.h"

int equipment1Open(int pinNum) 
{
	digitalWrite(pinNum, LOW);
	printw("-----------------------Equipment1 open seccess!----------------------\n");
}

int equipment1Close(int pinNum)
{
	digitalWrite(pinNum, HIGH);
	printw("-----------------------Equipment1 close seccess!---------------------\n");
}

int equipment1Init(int pinNum)
{
	pinMode(pinNum, OUTPUT);
	digitalWrite(pinNum, HIGH);
}

int equipment1Status(int pinNum)
{
	if(digitalRead(pinNum) == 1) {
		printw("-----------------------Equipment1 is open!-----------------------\n");
	} else {
		printw("-----------------------Equipment1 is close!----------------------\n");
	}
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




















