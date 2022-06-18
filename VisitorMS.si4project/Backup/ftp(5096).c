
#include "ftp.h"

/* 打开摄像头 */
void openFtp(int flag)
{
	/* 打印提示信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("---------------The log processing function is starting!--------------\n");
	printw("-----------Connect through the client and upload the log-------------\n");
	printw("---------------------./client 192.168.3.143 8000---------------------\n");
	printw("-----------Connect through the server and download the log-----------\n");
	printw("-----------------------------./server 8000---------------------------\n");
	printw("------------The instructions you can enter are as follows------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("            pwd---Displays the server current path                   \n");
	printw("            ls---Displays the server current directory file          \n");
	printw("            lls---Displays the client current directory file         \n");
	printw("            cd xxx---Switch the server directory                     \n");
	printw("            lcd xxx---Switch the client directory                    \n"); 
	printw("            get xxx---Download XXX file                              \n");
	printw("            put xxx---Upload XXX file                                \n");
	printw("            quit---Turn off the visitor management system            \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("----------------Enter ctrl + c to turn off the connect---------------\n");
	printw("----------------------Enter any key to to continue-------------------\n");
	refresh(); 
	getch();

	/* 返回shell界面，正常打印摄像头启动信息 */
	endwin();

	if (flag == 1) {
		system("./src/lib/ftp/ftp_server_start.sh");
	} else if (flag == 2) {
		system("./src/lib/ftp/ftp_client_start.sh");
	}
	
	/* 摄像头使用结束后，重新打开ncurses界面 */
	initNcurse();

	/* 刷新界面 */
	picRefresh();

	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	printw("----------The remote download log function close seccess!------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}

/* 关闭摄像头 */
void closeFtp(void)
{
	/* 打印退出信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------The remote download log function is already off!----------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();

	return;	
}




