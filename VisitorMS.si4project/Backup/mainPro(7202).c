
#include "mainPro.h"

int main()
{	
	/* 定义变量 */
	pthread_t pic_refresh_pthread; // 界面刷新线程 
	pthread_t function_pthread;  // 功能执行线程


	/* 初始化wiringPi库 */
		if (wiringPiSetup() == -1) {
			printf("wiringPi setup error\n");
			return -1;
		}
		
	/* 初始化ncurse库 */
	initNcurse();
		
	/* 打印身份验证界面 */
	picOfAuthenticationInterface();
	int selectFunction = 0;  // 选择功能 
	
	
	/* 根据用户输入打印不同界面 */
	while (1) {
		selectFunction = getch();
		//usleep(200000);
		move(0, 0);  //将界面打印的坐标移动到左上角
		switch (selectFunction)  //getch读到的是字符，为ASCII码，0对应的是49
		{
		case 49:
			picOfFunctionSelect_visitor();
			break;
		case 50:
			picOfFunctionSelect_user1();
			break;
		case 51:
			picOfFunctionSelect_user2();
			break;
		case 52:
			picOfFunctionSelect_administrators();
			break;
		default:
			printw("input error!\n");
		}
		refresh();  //刷新显示新的界面
	}




	/* 界面刷新线程 */
    pthread_create(&pic_refresh_pthread, NULL, (void *)picRefresh, NULL);
	/* 其他线程 */




	/* 程序结束处理 */
	endwin();
	return 0;	
}
