
#include "controlDevice.h"

int fireAlarmOpen(struct controlDevice *equipmentNode) 
{
	digitalWrite(equipmentNode->pinNum, LOW);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------FireAlarm is Always on!-----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int fireAlarmClose(struct controlDevice *equipmentNode)
{
	digitalWrite(equipmentNode->pinNum, HIGH);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("------------------The fire alarm has been turned off!----------------\n");
	printw("----------------Please pay attention to fire prevention--------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int fireStatusRead(struct controlDevice *equipmentNode)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");

	if(digitalRead(equipmentNode->pinNum) == 0) {
		printw("-----------------------Fire-alarm is open!---------------------------\n");
	} else {
		printw("-----------------------Fire-alarm is close!--------------------------\n");
	}
	
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int fireAlarmInit(struct controlDevice *equipmentNode)
{
	pinMode(equipmentNode->pinNum, OUTPUT);
	digitalWrite(equipmentNode->pinNum, LOW);
}

struct controlDevice fireAlarm = {
	.deviceName = "fireAlarm",
	.pinNum = 24,
	.deviceInit = fireAlarmInit,
	.readStatus = fireStatusRead,
	.open = fireAlarmOpen,
	.close = fireAlarmClose,
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




















