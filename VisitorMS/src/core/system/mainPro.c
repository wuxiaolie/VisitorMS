
/**********************************************************************************************
 *    :|x].              ?ObU:        +jfl           ?Zdr'                   '"I>>iI"'        
 *    n$$${             x@$$k;       n$$$Mi         [B$$$c               "-xZ*%$$$$$%*pX+     
 *    >8$$k`           j$$$C^       ]$$$$$Q.       `k$$$$8l            ~Y#$$%kQznnuY0qhk|     
 *     j$$$n          {@$$0'       .q$$$$$B<       ($$$$$$/          'uB$$p{:                 
 *     'm$$B+        +&$$b,        _@$$B$$$z      ;#$$8%$$Z.         +$$$M:                   
 *      !&$$b^      !*$$#!         C$$$\k$$M:    .Q$$@}X$$8!         ,w$$$bc|}-~<iI".         
 *       f$$$x     :k$$&+         _B$$p./$$$x    /$$$u +@$$x          '[YdW@$$$$$$$%oOr>      
 *       'w$$%~   ^w$$B}         `b$$@- "h$$Wl  _8$$O' 'p$$o"             ^:!><+](n0#$$@Z>    
 *        >8$$b^ 'L$$$\          x$$$C   )$$$C Io$$a;   ($$$t                       `[#$$*:   
 *         /$$$X.c$$$x          <8$$&l   .Z$$@\w$$%+    "a$$#;     ,]]"               p$$$>   
 *         .J$$@w$$$Y.         .O$$$n     >8$$$$$$t      \$$$J     0$$*\"         '!(p$$$u.   
 *          "d$$$$$Q'          >B$$%i      r$$$$$L.      ^a$$@{    _b$$$&qJvnnncCq#$$$&Q-     
 *           lh$$$Y'           [$$$U       `0$$@C^        {@$$a^    .+jQk&@$$$$$@&aOn[:       
 *            :\r]             '{x)^        .+}>           ?UJ).         ^:l>>>l:^.            
 *                                                                                           
 * Copyright (C) 2022 - 2023, HaoQing, <970407688@qq.com>.
 * <https://github.com/wuxiaolie/VisitorMS> & <https://gitee.com/yang-haoqing/visitor-ms.git>
 *
 * This software is licensed as described in the file COPYING, which you should have received 
 * as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell copies of 
 * the Software, and permit persons to whom the Software is furnished to do so, under 
 * the terms of the COPYING file.
 *
 *********************************************************************************************/

#include "mainPro.h"

/* 身份验证主函数 */
int identityRecognitionProcess(int numOfIdentity)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		       // 选择功能
	int resultOfRecognition = FALSE;       // 验证是否通过      ，通过-1，不通过-0 
	
	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfAuthenticationInterface();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			resultOfRecognition = passwordRecognitionProcess(numOfIdentity);
			goto recognition_off;
			break;
		case 50:
			resultOfRecognition = faceRecognitionProcess(numOfIdentity);
			goto recognition_off;
			break;
		case 51:
			resultOfRecognition = voiceRecognitionProcess(numOfIdentity);
			goto recognition_off;
			break;
		case 52:
			resultOfRecognition = AppRecognitionProcess(numOfIdentity);
			goto recognition_off;
			break;
		case 53:
			picOfForgetPassword();    // 忘记密码，打印提示界面，然后退出到上一级
			goto recognition_off;
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}

recognition_off:
	return resultOfRecognition;
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
			registeredUserProcess();
			break;
		case 50:
			snakeGameStart();
			break;
		case 51:
			chatRoomProcess();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;
}

/* 其他用户处理程序 */
void otherUsersProcess(void)
{
	/* 验证身份 */
	if(!identityRecognitionProcess(OTHERUSERS)) {
		picOfIdentityError();
		return;
	}

	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFunctionSelect_otherusers();	  

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			snakeGameStart();
			break;
		case 50:
			chatRoomProcess();
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
	if(!identityRecognitionProcess(USER1)) {
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
			usartControlDeviceProcess();
			break;
		case 54:
			socketControlDeviceProcess();
			break;
		case 55:
			chatRoomProcess();
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
	if(!identityRecognitionProcess(USER2)) {
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
			usartControlDeviceProcess();
			break;
		case 54:
			socketControlDeviceProcess();
			break;
		case 55:
			chatRoomProcess();
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
	if(!identityRecognitionProcess(ADMINISTRATORS)) {
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
			usartControlDeviceProcess();
			break;
		case 56:
			socketControlDeviceProcess();
			break;
		case 57:
			chatRoomProcess();
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
			otherUsersProcess();        
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
