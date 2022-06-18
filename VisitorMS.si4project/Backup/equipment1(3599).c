
#include "controlDevice.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int equipment1Open(struct controlDevice *equipmentNode) 
{
	//digitalWrite(equipmentNode->pinNum, LOW);
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
	
	/* 通过自己编写的驱动来控制 */
	int cmd = 0
	fd = open("/dev/pin4", O_RDWR);
    if (fd < 0) {
        printf("open /dev/pin4 failed!\r\n");
        perror("reason:");
    } else {
        printf("open /dev/pin4 success!\r\n");
    }
    fd = write(fd, &cmd, 1);
	close(fd);
	
	getch();

	/* 清屏 */
	picRefresh();
}

int equipment1Close(struct controlDevice *equipmentNode)
{
	//digitalWrite(equipmentNode->pinNum, HIGH);
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

	/* 通过自己编写的驱动来控制 */
	int cmd = 0
	fd = open("/dev/pin4", O_RDWR);
    if (fd < 0) {
        printf("open /dev/pin4 failed!\r\n");
        perror("reason:");
    } else {
        printf("open /dev/pin4 success!\r\n");
    }
    fd = write(fd, &cmd, 1);
	close(fd);
	
	getch();

	/* 清屏 */
	picRefresh();
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
	.pinNum = 4,
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




















