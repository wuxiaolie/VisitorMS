
#include "mainPro.h"

/*------------------------------------------------------------------------*/
	/* 界面刷新线程 */
    //pthread_create(&pic_refresh_pthread, NULL, (void *)picRefresh, NULL);
	/* 其他线程 */ 

/*------------------------------------------------------------------------*/



/* 访客处理程序 */
void visitorProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	int flag = 0;                      // 功能标志位

	/* 功能选择界面打印，并完成功能选择 */
	while (!flag) {
		picOfFunctionSelect_visitor();	   // 打印提示界面
		move(0, 0);  				       // 将界面打印的坐标移动到左上角
		refresh(); 					       // 刷新显示新的界面
		/* 选择功能 */
		selectFunction = getch();          // getch读到的是字符，为ASCII码，0对应的是49
		switch (selectFunction) {
		case 49:
			snakeGameStart();
			flag = 1;
			break;
		default:
			printw("====The input is invalid or the selected function is unavailable!====\n");
		}
	}
	

	return;
}

/* 用户1处理程序 */
void user1Process(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	int flag = 0;                      // 功能标志位

	/* 功能选择界面打印，并完成功能选择 */
	while (!flag) {
		picOfFunctionSelect_user1();	   // 打印提示界面
		move(0, 0);  				       // 将界面打印的坐标移动到左上角
		refresh(); 					       // 刷新显示新的界面
		/* 选择功能 */
		selectFunction = getch();          // getch读到的是字符，为ASCII码，0对应的是49
		switch (selectFunction) {
		case 49:
			snakeGameStart();
			flag = 1;
			break;
		default:
			printw("====The input is invalid or the selected function is unavailable!====\n");
		}
	}


	return;
}

/* 用户2处理程序 */
void user2Process(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	int flag = 0;                      // 功能标志位

	/* 功能选择界面打印，并完成功能选择 */
	while (!flag) {
		picOfFunctionSelect_user2();	   // 打印提示界面
		move(0, 0);  				       // 将界面打印的坐标移动到左上角
		refresh(); 					       // 刷新显示新的界面
		/* 选择功能 */
		selectFunction = getch();          // getch读到的是字符，为ASCII码，0对应的是49
		switch (selectFunction) {
		case 49:
			snakeGameStart();
			flag = 1;
			break;
		default:
			printw("====The input is invalid or the selected function is unavailable!====\n");
		}
	}


	
	
	return;
}


/* 管理员处理程序 */
void administratorsProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	int flag = 0;                      // 功能标志位

	/* 功能选择界面打印，并完成功能选择 */
	while (!flag) {
		picOfFunctionSelect_administrators();	   // 打印提示界面
		move(0, 0);  				       // 将界面打印的坐标移动到左上角
		refresh(); 					       // 刷新显示新的界面
		/* 选择功能 */
		selectFunction = getch();          // getch读到的是字符，为ASCII码，0对应的是49
		switch (selectFunction) {
		case 49:
			snakeGameStart();		
			flag = 1;
			break;
		default:
			printw("====The input is invalid or the selected function is unavailable!====\n");
		}
	}


	
	
	return;
}
















int main()
{	
	/* 定义变量 */
	pthread_t pic_refresh_pthread;     // 界面刷新线程 
	pthread_t function_pthread; 	   // 功能执行线程


	/* 初始化wiringPi库 */
		if (wiringPiSetup() == -1) {
			printf("wiringPi setup error\n");
			return -1;
		}
		
	/* 初始化ncurse库 */
	initNcurse();
		
	/* 打印身份验证界面 */
	picOfAuthenticationInterface();
	int selectFunction = 0; 		   // 选择功能 
	
	/* 根据用户输入打印不同界面 */
	while (1) {
		//usleep(200000);
		selectFunction = getch();      // getch读到的是字符，为ASCII码，0对应的是49
		move(0, 0);  				   // 将界面打印的坐标移动到左上角
		
		switch (selectFunction) {
		case 49: 					   // 这里可以将数字改为宏定义
			move(0, 0);  			   // 将界面打印的坐标移动到左上角
			visitorProcess();
			break;
		case 50:
			move(0, 0);  			   // 将界面打印的坐标移动到左上角
			user1Process();
			break;
		case 51:	
			move(0, 0);  			   // 将界面打印的坐标移动到左上角
			user2Process();
			break;
		case 52:
			move(0, 0);  			   // 将界面打印的坐标移动到左上角
			administratorsProcess();
			break;
		default:
			picOfAuthenticationInterfacePro();
		}

		refresh(); 					   // 刷新显示新的界面
	}



	/* 程序结束处理 */
	endwin();
	return 0;	
}
