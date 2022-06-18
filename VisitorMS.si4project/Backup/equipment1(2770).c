
#include "controlDevice.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "menu.h"

int equipment1Open(struct controlDevice *equipmentNode) 
{
	/* 返回shell界面 */
	endwin();

	/* 执行脚本 */
	system("./src/lib/drivers/pin4driver_start.sh");
		
	/* 结束后，重新打开ncurses界面 */
	initNcurse();

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

#if 0
	//digitalWrite(equipmentNode->pinNum, LOW);
	/* 通过自己编写的驱动来控制 */
	int cmd = 0;
	int fd;
	fd = open("/dev/pin4", O_RDWR);
    if (fd < 0) {
    //    printf("open /dev/pin4 failed!\r\n");
    //    perror("reason:");
    } else {
        fd = write(fd, &cmd, 1);
    //    printf("open /dev/pin4 success!\r\n");
    }
	close(fd);
	fflush(stdin);
	fflush(stdout);
	
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

	/* 清屏 */
	//picRefresh();
#endif
}

int equipment1Close(struct controlDevice *equipmentNode)
{
	/* 返回shell界面 */
	endwin();

	/* 执行脚本 */
	system("./src/lib/drivers/pin4driver_start.sh");
		
	/* 结束后，重新打开ncurses界面 */
	initNcurse();

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


#if 0
	//digitalWrite(equipmentNode->pinNum, HIGH);
	/* 通过自己编写的驱动来控制 */
	int fd;
	int cmd = 1;
	fd = open("/dev/pin4", O_RDWR);
    if (fd < 0) {
    //    printf("open /dev/pin4 failed!\r\n");
    //    perror("reason:");
    } else {
    	fd = write(fd, &cmd, 1);
    //    printf("open /dev/pin4 success!\r\n");
    }
    close(fd);
	fflush(stdin);
	fflush(stdout);
	
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

	/* 清屏 */
	//picRefresh();
#endif
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




















