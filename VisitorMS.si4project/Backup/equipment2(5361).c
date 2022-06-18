
#include "controlDevice.h"

int equipment2Open(struct controlDevice *equipmentNode) 
{
	digitalWrite(equipmentNode->pinNum, LOW);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment2 open seccess!----------------------\n");
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

int equipment2Close(struct controlDevice *equipmentNode)
{
	digitalWrite(equipmentNode->pinNum, HIGH);
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Equipment2 close seccess!---------------------\n");
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

int equipment2Init(struct controlDevice *equipmentNode)
{
	pinMode(equipmentNode->pinNum, OUTPUT);
	digitalWrite(equipmentNode->pinNum, HIGH);
}

int equipment2Status(struct controlDevice *equipmentNode)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");

	if(digitalRead(equipmentNode->pinNum) == 0) {
		printw("-----------------------Equipment2 is open!---------------------------\n");
	} else {
		printw("-----------------------Equipment2 is close!--------------------------\n");
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


struct controlDevice equipment2 = {
	.deviceName = "equipment2",
	.pinNum = 22,
	.open = equipment2Open,
	.close = equipment2Close,
	.deviceInit = equipment2Init,
	.readStatus = equipment2Status,
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





















