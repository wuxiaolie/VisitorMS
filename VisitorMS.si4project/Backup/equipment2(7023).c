
#include "controlDevice.h"

int equipment2Open(struct controlDevice *equipmentNode) 
{
	digitalWrite(equipmentNode->pinNum, LOW);
	printw("-----------------------Equipment2 open seccess!----------------------\n");
}

int equipment2Close(struct controlDevice *equipmentNode)
{
	digitalWrite(equipmentNode->pinNum, HIGH);
	printw("-----------------------Equipment2 close seccess!---------------------\n");
}

int equipment2Init(struct controlDevice *equipmentNode)
{
	pinMode(equipmentNode->pinNum, OUTPUT);
	digitalWrite(equipmentNode->pinNum, HIGH);
}

int equipment2Status(struct controlDevice *equipmentNode)
{
	if(digitalRead(equipmentNode->pinNum) == 1) {
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





















