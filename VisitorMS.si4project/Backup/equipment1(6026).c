
#include "controlDevice.h"

int equipment1Open(struct controlDevice *equipmentNode) 
{
	digitalWrite(equipmentNode->pinNum, LOW);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment1 open seccess!----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int equipment1Close(struct controlDevice *equipmentNode)
{
	digitalWrite(equipmentNode->pinNum, HIGH);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment1 close seccess!---------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

int equipment1Init(struct controlDevice *equipmentNode)
{
	pinMode(equipmentNode->pinNum, OUTPUT);
	digitalWrite(equipmentNode->pinNum, HIGH);
}

int equipment1Status(struct controlDevice *equipmentNode)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");

	if(digitalRead(equipmentNode->pinNum) == 0) {
		printw("-----------------------Equipment1 is open!---------------------------\n");
	} else {
		printw("-----------------------Equipment1 is close!--------------------------\n");
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


struct controlDevice equipment1 = {
	.deviceName = "equipment1",
	.pinNum = 21,
	.open = equipment1Open,
	.close = equipment1Close,
	.deviceInit = equipment1Init,
	.readStatus = equipment1Status,
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




















