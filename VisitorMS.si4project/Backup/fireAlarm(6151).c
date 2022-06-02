
#include "controlDevice.h"

int fireStatusRead(int pinNum)
{
	if(digitalRead(pinNum) == 1) {
		printw("-----------------------Fire-alarm is open!-----------------------\n");
	} else {
		printw("-----------------------Fire-alarm is close!----------------------\n");
	}
}

int fireAlarmInit(int pinNUm)
{
	pinMode(pinNUm, OUTPUT);
	digitalWrite(pinNUm, HIGH);
}

struct controlDevice fireAlarm = {
	.deviceName = "fireAlarm",
	.pinNum = 24,
	.deviceInit = fireAlarmInit,
	.readStatus = fireStatusRead,
};

/* 头插法 */
struct controlDevice *addfireAlarmToDevices(struct controlDevice *phead)
{
	if (phead == NULL) {
		return &fireAlarm;
	} else {
		fireAlarm.next = phead;
		phead = &fireAlarm;
	}
}




















