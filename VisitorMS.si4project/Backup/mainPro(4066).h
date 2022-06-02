
#include "controlDevice.h"
#include "identityRecognition.h"
#include "inputCommand.h"
#include "menu.h"
#include "snake.h"
#include "camera.h"
#include "ftp.h"

/* 将串口/语音/网络接受到的指令宏定义 */
#define OPEN1	  20
#define OPEN2     21   
#define CLOSE1    22   
#define CLOSE2    23

/* 定义全局变量 */
struct controlDevice *pdeviceHead = NULL;
struct inputCommand *pcommandHead = NULL;
struct inputCommand *socketHead = NULL;
int c_fd;

/* 定义mainFunctionInit函数需要的变量 */
char name[128];
pthread_t chatThread;	
pthread_t voiceThread;	
pthread_t usartThread;
pthread_t socketThread;
pthread_t socketReadThread;

struct controlDevice *tmp = NULL;

/**********************************************************************
 * 函数名称： findDeviceByName
 * 功能描述： 设备链表中查找结点
 * 输入参数： name - 名字，phead - 链表头结点
 * 输出参数： 无
 * 返 回 值： 返回结点指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
struct controlDevice *findDeviceByName(char *name, struct controlDevice *phead)
{
	struct controlDevice *tmp = phead;
	if (phead == NULL) {
		return NULL;
	} else {
		while (tmp != NULL) {
			if (strcmp(tmp->deviceName, name) == 0) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
}

/**********************************************************************
 * 函数名称： findCommandByName
 * 功能描述： 指令链表中查找结点
 * 输入参数： name - 名字，phead - 链表头结点
 * 输出参数： 无
 * 返 回 值： 返回结点指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
struct inputCommand *findCommandByName(char *name, struct inputCommand *phead)
{
	struct inputCommand *tmp = phead;
	if (phead == NULL) {
		return NULL;
	} else {
		while (tmp != NULL) {
			if (strcmp(tmp->commandName, name) == 0) {
				return tmp;
			}
			tmp = tmp->next;
		}
	}
}

/**********************************************************************
 * 函数名称： doInputCommand
 * 功能描述： 判断语言/网络指令类型
 * 输入参数： 字符串指令
 * 输出参数： 无
 * 返 回 值： int
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ***********************************************************************/
/* 判断语言/网络指令类型 */
int doInputCommand(char *cmd)
{
	if (!strcmp("open1", cmd))
	{
		struct controlDevice *equipment1Node = NULL;
		/* 从设备链表中查找设备 */
		equipment1Node = findDeviceByName("equipment1", pdeviceHead);
		/* 初始化设备 */
		equipment1Node->deviceInit(equipment1Node);
		/* 打开设备1 */
		equipment1Node->open(equipment1Node);
		return OPEN1;
	}
	if (!strcmp("open2", cmd))
	{
		struct controlDevice *equipment2Node = NULL;
		/* 从设备链表中查找设备 */
		equipment2Node = findDeviceByName("equipment2", pdeviceHead);
		/* 初始化设备 */
		equipment2Node->deviceInit(equipment2Node);
		/* 打开设备2 */
		equipment2Node->open(equipment2Node);
		return OPEN2;
	}
	if (!strcmp("close1", cmd))
	{
		struct controlDevice *equipment1Node = NULL;
		/* 从设备链表中查找设备 */
		equipment1Node = findDeviceByName("equipment1", pdeviceHead);
		/* 初始化设备 */
		equipment1Node->deviceInit(equipment1Node);
		/* 打开设备1 */
		equipment1Node->close(equipment1Node);
		return CLOSE1;
	}
	if (!strcmp("close2", cmd))
	{
		struct controlDevice *equipment2Node = NULL;
		/* 从设备链表中查找设备 */
		equipment2Node = findDeviceByName("equipment2", pdeviceHead);
		/* 初始化设备 */
		equipment2Node->deviceInit(equipment2Node);
		/* 打开设备2 */
		equipment2Node->close(equipment2Node);
		return CLOSE2;
	}
	
	//printf("The instruction passed in is invalid!\r\n");
	//其他指令未定义，返回-1表示未找到
	return -1;
}

/**********************************************************************
 * 函数名称： chat_thread
 * 功能描述： 聊天室服务端处理线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/29	V1.0   杨皓清	        创建
 ***********************************************************************/
void *chat_thread(void *data)
{
	system("./lib/chat/chat_server_start.sh");
}

/**********************************************************************
 * 函数名称： usart_thread
 * 功能描述： 串口控制处理线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/25	V1.0   杨皓清	        创建
 ***********************************************************************/
void *usart_thread(void *data)
{
	struct inputCommand *usartHead = NULL;
	int nread;
	
	usartHead = findCommandByName("usart", pcommandHead);
	
	if (usartHead == NULL) {
		printf("Find usartHandler error!\r\n");
		pthread_exit(NULL);   //线程调用此函数来退出
	} else {
		int flag = 0;
		flag = usartHead->initCommand(usartHead, NULL, NULL);
		if (flag == -1) {
			pthread_exit(NULL);   //线程调用此函数来退出
		}
		
		//打印串口模块初始化成功信息
		printf("--------------------------------\r\n");
		printf("Usart module connection succeeded.\r\n");
		printf("--------------------------------\r\n");
		
		while (1) {
			nread = usartHead->getCommand(usartHead);
			if (nread == 0) {

				/* 未获取到语音（串口）消息，无需打印信息 */
				//	printf("nodata from usart\n");
			} else {
				printf("usart pthread get command: %s\r\n",  usartHead->commandID);
				int ret = 0;
				ret = doInputCommand(usartHead->commandID);
			}
			sleep(3);
		}	
	}
}

/**********************************************************************
 * 函数名称： voice_thread
 * 功能描述： 语音模块处理线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ***********************************************************************/
void *voice_thread(void *data)
{
	struct inputCommand *voiceHead = NULL;
	int nread;
	
	voiceHead = findCommandByName("voice", pcommandHead);
	
	if (voiceHead == NULL) {
		printf("Find voiceHandler error!\r\n");
		pthread_exit(NULL);   //线程调用此函数来退出
	} else {
		int flag = 0;
		flag = voiceHead->initCommand(voiceHead, NULL, NULL);
		if (flag == -1) {
			pthread_exit(NULL);   //线程调用此函数来退出
		}
		
		//打印语音模块初始化成功信息
		printf("--------------------------------\r\n");
		printf("Voice module connection succeeded.\r\n");
		printf("--------------------------------\r\n");
		
		while (1) {
			nread = voiceHead->getCommand(voiceHead);
			if (nread == 0) {

				/* 未获取到语音（串口）消息，无需打印信息 */
				//	printf("nodata from voice\n");
			} else {
				printf("Voice pthread get command: %s\r\n",  voiceHead->commandID);
				int ret = 0;
				ret = doInputCommand(voiceHead->commandID);
			}
			sleep(3);
		}	
	}
}

/**********************************************************************
 * 函数名称： socket_read_thread
 * 功能描述： socket读取线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ***********************************************************************/
void *socket_read_thread(void *data)
{
	int n_read;
	
	while (1) {
		//清空
		memset(socketHead->commandID, '\0', sizeof(socketHead->commandID));
		n_read = read(c_fd, socketHead->commandID, sizeof(socketHead->commandID));

		if (n_read == -1) {
			perror("Socket read command error ");
			pthread_exit(NULL);
		} else if (n_read > 0) {
			printf("Socket pthread get command: %dbytes , %s\r\n", n_read, socketHead->commandID);
			int ret = 0;
			ret = doInputCommand(socketHead->commandID);

			//由于执行指令时显示新界面，通过getch暂停，再打印会干扰getch
			//if (ret == -1) {
			//	printf("Instruction execution failed!\r\n");
			//} else {
			//	printf("Instruction execution success!\r\n");
			//}
		} else {
			printf("The client is quit!\r\n");
			pthread_exit(NULL);
		}
		//sleep(1);
	}
}

/**********************************************************************
 * 函数名称： socket_thread
 * 功能描述： socket处理线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ***********************************************************************/
void *socket_thread(void *data)
{
	int n_read = 0;
	struct sockaddr_in c_addr;
	
	memset(&c_addr, 0, sizeof(struct sockaddr_in));
	int clen = sizeof(struct sockaddr_in);
			
	socketHead = findCommandByName("socket", pcommandHead);
	if (socketHead == NULL) {
		printf("Find socketHandler error!\r\n");
		pthread_exit(NULL);
	}

	/* 初始化 */
	socketHead->initCommand(socketHead, NULL, NULL);	

	while (1) {
		/* 4.accept，进入阻塞状态，获取客户端的连接请求，并建立连接 */
		c_fd = accept(socketHead->sfd, (struct sockaddr *)&c_addr, &clen);
		//输出错误信息
		if(c_fd == -1) {
			perror("Failed to establish connection ");
		}

		//打印客户端IP地址
		printf("--------------------------------\r\n");
		printf("Client connection succeeded.\r\n");
		printf("The IP address of the client is:  %s\r\n",inet_ntoa(c_addr.sin_addr));
		printf("--------------------------------\r\n");
		
		/* 新建一个套接字读取线程，原线程可继续接收其他客户端的连接 */
		pthread_create(&socketReadThread, NULL, socket_read_thread, NULL);
		
	}
}

/**********************************************************************
 * 函数名称： mainFunctionProgram
 * 功能描述： 设备初始化工作
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ***********************************************************************/
void mainFunctionInit(void)
{
	/* 1.指令工厂初始化 */
	pcommandHead = addvoiceControlToCommand(pcommandHead);
	pcommandHead = addsocketControlToCommand(pcommandHead);
	pcommandHead = addusartControlToCommand(pcommandHead);

	/* 2.设备控制工厂初始化 */
	pdeviceHead = addequipment1ToDevices(pdeviceHead);
	pdeviceHead = addequipment2ToDevices(pdeviceHead);
	pdeviceHead = addfireAlarmToDevices(pdeviceHead);
}

/* --------------------------------------------------------------------------------
 * 设备功能控制
 * --------------------------------------------------------------------------------
 * 2022/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 设备控制的串口线程处理函数 */
void usartControlDeviceProcess(void)
{
	/* 语音控制提示界面 */
    picOfUsartControl();
	
	/* 创建语音线程 */
	pthread_create(&usartThread, NULL, usart_thread, NULL);
	
	/* 打印提示信息 */
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("--------------------------------\r\n");
	printf("Usart thread created successfully.\r\n");

	/* 卡住界面，配合picOfSocketControl函数显示界面，同时也让子线程等待客户端连接 */
	getch();

	///* 等待线程退出 */
	//pthread_join(usartThread, NULL);
}

/* 设备控制的语音线程处理函数 */
void voiceControlDeviceProcess(void)
{
	/* 语音控制提示界面 */
    picOfVoiceControl();
	
	/* 创建语音线程 */
	pthread_create(&voiceThread, NULL, voice_thread, NULL);
	
	/* 打印提示信息 */
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("--------------------------------\r\n");
	printf("Voice thread created successfully.\r\n");

	/* 卡住界面，配合picOfSocketControl函数显示界面，同时也让子线程等待客户端连接 */
	getch();

	///* 等待线程退出 */
	//pthread_join(voiceThread, NULL);
}

/* 设备控制的网络线程处理函数 */
void socketControlDeviceProcess(void)
{
	/* 网络控制提示界面 */
	picOfSocketControl();

	/* 创建socket线程 */
	pthread_create(&socketThread, NULL, socket_thread, NULL);

	/* 打印提示信息 */
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("--------------------------------\r\n");
	printf("Socket thread created successfully.\r\n");

	/* 卡住界面，配合picOfSocketControl函数显示界面，同时也让子线程等待客户端连接 */
	getch();

	/* 阻塞等待线程退出 */
	//pthread_join(socketThread, NULL);
}

/* 设备1控制处理函数 */
void equipment1Process(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *equipment1Node = NULL;

	/* 从设备链表中查找设备 */
	equipment1Node = findDeviceByName("equipment1", pdeviceHead);

	/* 初始化设备 */
	equipment1Node->deviceInit(equipment1Node);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment1Node->open(equipment1Node);
			break;
		case 50:
			equipment1Node->close(equipment1Node);
			break;
		case 51:
			equipment1Node->readStatus(equipment1Node);
			break;
		case 113:
			break;
		default:
	        picOfInputError();         
		}
	}
	
	return;
}


/* 设备2控制处理函数 */
void equipment2Process(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *equipment2Node = NULL;

	/* 从设备链表中查找设备 */
	equipment2Node = findDeviceByName("equipment2", pdeviceHead);

	/* 初始化设备 */
	equipment2Node->deviceInit(equipment2Node);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			equipment2Node->open(equipment2Node);
			break;
		case 50:
			equipment2Node->close(equipment2Node);
			break;
		case 51:
			equipment2Node->readStatus(equipment2Node);
			break;
		case 113:
			break;
		default:
			picOfInputError();   
		}
	}
	
	return;
}

/* 设备3控制处理函数 */
void fireAlarmProcess(void) 
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能
	struct controlDevice *fireAlarmNode = NULL;

	/* 从设备链表中查找设备 */
	fireAlarmNode = findDeviceByName("fireAlarm", pdeviceHead);

	/* 初始化设备 */
	fireAlarmNode->deviceInit(fireAlarmNode);

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfEquipmentFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			fireAlarmNode->open(fireAlarmNode);
			break;
		case 50:
			fireAlarmNode->close(fireAlarmNode);
			break;
		case 51:
			fireAlarmNode->readStatus(fireAlarmNode);
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;
}

/* 摄像头控制处理函数 */
void cameraProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfCameraFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			openCamera();
			break;
		case 50:
			closeCamera();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;

}

/* 下载日志处理函数 */
void downloadLogProcess(void)
{
	/* 局部变量定义 */
	int selectFunction = 0; 		   // 选择功能

	/* 功能选择界面打印，并完成功能选择 */
	while (selectFunction != 113) {

		/* 打印提示界面 */
		picOfFtpFunctionSelect();

		/* 选择功能 */
		selectFunction = getch();        
		switch (selectFunction) {
		case 49:
			openFtp(1);
			break;
		case 50:
			openFtp(2);
			break;
		case 51:
			openFtp(2);
			break;
		case 52:
			closeFtp();
			break;
		case 113:
			break;
		default:
			picOfInputError();
		}
	}
	
	return;

}

/* 聊天室处理函数 */
void chatRoomProcess(void)
{
	/* 创建chat线程 */
	pthread_create(&chatThread, NULL, chat_thread, NULL);

	/* 打印提示信息 */
	picOfChatRoomFunction();

	/* 返回shell界面，调用聊天室打开脚本 */
	endwin();
	system("./src/lib/chat/chat_client_start.sh");

	/* 退出前，结束聊天室服务端线程 */
	pthread_cancel(chatThread);
	
	/* 回收线程 */
	pthread_join(chatThread, NULL);

	/* 聊天室结束运行后，重新打开ncurses界面 */
	initNcurse();

	/* 清屏 */
	picRefresh();

	/* 打印退出信息 */
	picOfChatRoomEnd();

	/* 清屏 */
	picRefresh();

	return; 	
}

/* 注册用户处理函数 */
void registeredUserProcess(void)
{


	return;
}

/* --------------------------------------------------------------------------------
 * 识别功能实现
 * --------------------------------------------------------------------------------
 * 2022/05/23	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 人脸识别处理函数 */
int faceRecognitionProcess(int numOfIdentity) 
{
	/* 打印提示界面，让用户把照片放到指定位置并命名为指定名称 */
	picOfFaceRecognition();

	int resultOfRecognition = FALSE;
	resultOfRecognition = faceRecognitionMain(numOfIdentity);

	/* 暂停界面-让用户查看运行中打印的信息 */
	printf("Enter any key to return ...\r\n");
	getch();

	/* 清屏 */
	picRefresh();
	return resultOfRecognition;
}

/* 口令识别处理函数 - 直接通过控制工厂 - 打开串口设备，读取信息 */
int voiceRecognitionProcess(int numOfIdentity) 
{
	/* 打印提示界面，让用户对着麦克风说出解锁/识别口令 */
	picOfVoiceRecognition();

	struct inputCommand *usartHead = NULL;
	int nread;
	
	usartHead = findCommandByName("usart", pcommandHead);
	
	if (usartHead == NULL) {
		printf("Find usartHandler error!\r\n");
		return FALSE;
	} else {
		int flag = 0;
		flag = usartHead->initCommand(usartHead, NULL, NULL);
		if (flag == -1) {
			goto voice_recognition_return;
			return FALSE;
		}
		//打印串口模块初始化成功信息
		printf("--------------------------------\r\n");
		printf("Usart module connection succeeded.\r\n");
		printf("--------------------------------\r\n");

		int nodeNum = 0;
		while (1) {
			nread = usartHead->getCommand(usartHead);
			if (nread == 0) {
				/* 未获取到语音（串口）消息，无需打印信息 */
				printf("...");
				/* 每打印8次...，然后打印一次回车换行 */
				nodeNum++;
				if (nodeNum == 8) {
					printf("\r\n");
					nodeNum = 0;
				}
			} else {
				printf("Usart module get command: %s\r\n",  usartHead->commandID);
				if (!strcmp("42123954", usartHead->commandID)) {
					printf("Congratulations, voice verification passed.\r\n");
					break;
				} else {
					printf("Sorry, voice verification failed.\r\n");
 					printf("Enter q to exit, otherwise continue verification.\r\n");
					if (getch() == 113) {
						break;
					}
				}
			}
			sleep(2);
		}	
	}

voice_recognition_return:
	/* 暂停界面-让用户查看运行中打印的信息 */
	printf("Enter any key to return ...\r\n");
	getch();

	/* 清屏 */
	picRefresh();
	return FALSE;

}

/* 密码识别处理函数 */
int passwordRecognitionProcess(int numOfIdentity) 
{
	/* 打印提示界面， */
	picOfPasswordRecognition();

	int resultOfRecognition = FALSE;
	resultOfRecognition = passwordRecognitionMain(numOfIdentity);

	/* 暂停界面-让用户查看运行中打印的信息 */
	printf("Enter any key to return ...\r\n");
	getch();

	/* 清屏 */
	picRefresh();
	return resultOfRecognition;
} 


/* APP识别处理函数 */
int AppRecognitionProcess(int numOfIdentity) 
{
	/* 打印提示界面， */
	picOfAppRecognition();

	
	int resultOfRecognition = FALSE;
	//resultOfRecognition = AppRecognitionMain(numOfIdentity);

	/* 暂停界面-让用户查看运行中打印的信息 */
	printf("Enter any key to return ...\r\n");
	getch();

	/* 清屏 */
	picRefresh();
	return resultOfRecognition;
}

















