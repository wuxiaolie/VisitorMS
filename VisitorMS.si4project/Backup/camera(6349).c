
#include "camera.h"

/* 打开摄像头 */
void openCamera(void)
{
	/* 打印提示信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("--------------------------Camera is starting!------------------------\n");
	printw("----------------------Open web page to view video--------------------\n");
	printw("----------------http://192.168.3.143:8080/index.html-----------------\n");
	printw("----------------Enter ctrl + c to turn off the camera----------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("\n");
	printw("\n");
	printw("----------------------Enter any key to to continue-------------------\n");
	refresh(); 
	getch();

	/* 返回shell界面，正常打印摄像头启动信息 */
	endwin();

	/* 打开树莓派摄像头 */
	system("/home/pi/raspberry/mjpg-streamer/mjpg-streamer-experimental/start.sh");

	/* 摄像头使用结束后，重新打开ncurses界面 */
	initNcurse();

	/* 刷新界面 */
	//picRefresh();

	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Camera close seccess!-------------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}

/* 关闭摄像头 */
void closeCamera(void)
{
	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------------------The camera is already off!----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}




