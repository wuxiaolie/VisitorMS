
#include "mainPro.h"

/* 身份验证主函数 */
int identityRecognitionProcess(int index)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfAuthenticationInterface();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			passwordRecognitionProcess();
			break;
		case 50:
			faceRecognitionProcess();
			break;
		case 51:
			voiceRecognitionProcess();
			break;
		case 52:
			AppRecognitionProcess();
			break;	
		case 53:
			picOfForgetPassword();
			selectFunction = 113;       // 忘记密码，打印提示界面，然后退出到上一级
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return index;
}

/* 访客处理程序(访客无需验证身份) */
void visitorProcess(void)
{
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
		case 52:
			voiceControlDeviceProcess();
			break;
		case 53:
			socketControlDeviceProcess();
			break;
		case 113:
			break;
		default:
			break;
			//picOfInputError();          //由于其他线程的输入会干扰，所以这里关闭报错
		}
	}

	/* 清屏 */
	picRefresh(); 

	/* 退出前，结束语言或者网络线程 */
	pthread_cancel(voiceThread);
	pthread_cancel(socketReadThread);
	pthread_cancel(socketThread);
	
	/* 回收线程 */
	pthread_join(voiceThread, NULL);
	pthread_join(socketReadThread, NULL);
	pthread_join(socketThread, NULL);

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
		case 52:
			voiceControlDeviceProcess();
			break;
		case 53:
			socketControlDeviceProcess();
			break;
		case 113:
			break;
		default:
			break;
			//picOfInputError();          //由于其他线程的输入会干扰，所以这里关闭报错
		}
	}

	/* 清屏 */
	picRefresh(); 

	/* 退出前，结束语言或者网络线程 */
	pthread_cancel(voiceThread);
	pthread_cancel(socketReadThread);
	pthread_cancel(socketThread);
	
	/* 回收线程 */
	pthread_join(voiceThread, NULL);
	pthread_join(socketReadThread, NULL);
	pthread_join(socketThread, NULL);

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
		case 53:
			downloadLogProcess();
			break;
		case 54:
			voiceControlDeviceProcess();
			break;
		case 55:
			socketControlDeviceProcess();
			break;
		case 113:
			break;
		default:
			break;
			//picOfInputError();          //由于其他线程的输入会干扰，所以这里关闭报错
		}
	}

	/* 清屏 */
	picRefresh(); 

	/* 退出前，结束语言或者网络线程 */
	pthread_cancel(voiceThread);
	pthread_cancel(socketReadThread);
	pthread_cancel(socketThread);
	
	/* 回收线程 */
	pthread_join(voiceThread, NULL);
	pthread_join(socketReadThread, NULL);
	pthread_join(socketThread, NULL);

	return;

}

/* main主程序 */
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
		case 53:
			visitorProcess();          // 其他使用者，这里暂时没有为其扩展功能，可以补充登记、申请注册的程序
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
