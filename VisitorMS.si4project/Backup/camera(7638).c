
#include "camera.h"

/* 打开摄像头 */
void openCamera(void)
{
	/* 打印提示信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("-------------------------Camera open seccess!------------------------\n");
	printw("----------------------Open web page to view video--------------------\n");
	printw("----------------http://192.168.3.143:8080/index.html-----------------\n");
	printw("------------------------Enter Ctrl + c to quit-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 

	/* 打开树莓派摄像头 */
	system("/home/pi/raspberry/mjpg-streamer/mjpg-streamer-experimental/start.sh");

	/* 刷新界面 */
	picRefresh();

	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------------------Camera close seccess!-------------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();

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
	printw("---------------------------------------------------------------------\n");
	printw("---------------------The camera is already off!----------------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();

	return;	
}




