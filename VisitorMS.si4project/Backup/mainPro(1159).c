
#include "mainPro.h"

/*------------------------------------------------------------------------*/
	/* 界面刷新线程 */
    //pthread_create(&pic_refresh_pthread, NULL, (void *)picRefresh, NULL);
	/* 其他线程 */ 

/*------------------------------------------------------------------------*/

/* 身份验证主函数 */
int identityRecognitionProcess(int index)
{
	/* 身份验证界面 */
	picOfAuthenticationInterface();
    getch();
	return 1;
}


/* 访客处理程序 */
void visitorProcess(void)
{
	/* 验证身份 */
	if(!identityRecognitionProcess(1)) {
		picOfIdentityError();
		return;
	}

	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFunctionSelect_visitor();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			snakeGameStart();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	

	return;
}

/* 用户1处理程序 */
void user1Process(void)
{
	/* 验证身份 */
	if(!identityRecognitionProcess(1)) {
		picOfIdentityError();
		return;
	}

	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFunctionSelect_user1();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment1Process();
			break;
		case 50:
			equipment2Process();
			break;
		case 51:
			fireAlarmProcess();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	

	return;
}

/* 用户2处理程序 */
void user2Process(void)
{
	/* 验证身份 */
	if(!identityRecognitionProcess(1)) {
		picOfIdentityError();
		return;
	}

	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFunctionSelect_user2();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment1Process();
			break;
		case 50:
			fireAlarmProcess();
			break;
		case 51:
			cameraProcess();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	

	return;

}


/* 管理员处理程序 */
void administratorsProcess(void)
{
	/* 验证身份 */
	if(!identityRecognitionProcess(1)) {
		picOfIdentityError();
		return;
	}

	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFunctionSelect_administrators();	  

	    /* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment1Process();
			break;
		case 50:
			equipment2Process();
			break;
		case 51:
			fireAlarmProcess();
			break;
		case 52:
			cameraProcess();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;

}
















int main()
{	
	/* 定义变量 */
	int selectFunction = 0; 		   // 选择功能 
	pthread_t pic_refresh_pthread;     // 界面刷新线程 
	pthread_t function_pthread; 	   // 功能执行线程

	/* 初始化wiringPi库 */
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup error\n");
		return -1;
	}
	
	/* 初始化ncurse库 */
	initNcurse();

	/* 初始化设备工厂 */
	mainFunctionInit();
		
	/* 根据用户输入调整不同处理函数 */
	while (1) {

		/* 打印选择身份登录界面 */
		picOfSelectIdentity();

		selectFunction = getch();      // getch读到的是字符，为ASCII码，1对应的是49

		switch (selectFunction) {
		case 49: 					   // 这里可以将数字改为宏定义
			visitorProcess();
			break;
		case 50:
			user1Process();
			break;
		case 51:	
			user2Process();
			break;
		case 52:
			administratorsProcess();
			break;
		case 113:
			goto log_off;
		default:
			picOfInputError();
		}
	}



log_off:
	/* 程序结束处理 */
	endwin();
	return 0;	
}
