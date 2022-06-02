
#include "controlDevice.h"
#include "inputCommand.h"
#include "identityRecognition.h"
#include "menu.h"
#include "snake.h"


/* 定义全局变量 */
struct controlDevice *pdeviceHead = NULL;
struct inputCommand *pcommandHead = NULL;
struct inputCommand *socketHead = NULL;
int c_fd;

/* 定义mainFunctionInit函数需要的变量 */
char name[128];
pthread_t voiceThread;	
pthread_t socketThread;
struct controlDevice *tmp = NULL;

/**********************************************************************
 * 函数名称： findDeviceByName
 * 功能描述： 设备链表中查找结点
 * 输入参数： name - 名字，phead - 链表头结点
 * 输出参数： 无
 * 返 回 值： 返回结点指针
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2012/05/18	V1.0   杨皓清	        创建
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
 * 2012/05/18	V1.0   杨皓清	        创建
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
 * 函数名称： voice_thread
 * 功能描述： 语音模块处理线程
 * 输入参数： data - 数据
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2012/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void *voice_thread(void *data)
{
	struct inputCommand *voiceHead = NULL;
	int nread;
	
	voiceHead = findCommandByName("voice", pcommandHead);
	
	if (voiceHead == NULL) {
		printf("find voiceHandler error\n");
		pthread_exit(NULL);
	} else {
		voiceHead->initCommand(voiceHead, NULL, NULL);
		printf("%s init success\n", voiceHead->commandName);
		int i = 2;
		while (i--) {
			nread = voiceHead->getCommand(voiceHead);
			if (nread == 0) {
				printf("nodata from voice\n");
			} else {
				printf("do device control:%s\n", voiceHead->commandID);
			}
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
 * 2012/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void *socket_read_thread(void *data)
{
	int n_read;
	
	while (1) {
		//清空
		memset(socketHead->commandID, '\0', sizeof(socketHead->commandID));
		n_read = read(c_fd, socketHead->commandID, sizeof(socketHead->commandID));
		if (n_read == -1) {
			perror("read");
		} else if (n_read > 0) {
			printf("get command: %d,%s\n", n_read, socketHead->commandID);
		} else {
			printf("client quit\n");
		}
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
 * 2012/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void *socket_thread(void *data)
{
	int n_read = 0;
	struct sockaddr_in c_addr;
	
	memset(&c_addr, 0, sizeof(struct sockaddr_in));
	int clen = sizeof(struct sockaddr_in);
	
	pthread_t socketReadThread;
			
	socketHead = findCommandByName("socket", pcommandHead);
	if (socketHead == NULL) {
		printf("find voiceHandler error\n");
		pthread_exit(NULL);
	}
	socketHead->initCommand(socketHead, NULL, NULL);	
	printf("%s init success\n", socketHead->commandName);
	while (1) {
		/* 4.accept，进入阻塞状态，获取客户端的连接请求，并建立连接 */
		c_fd = accept(socketHead->sfd, (struct sockaddr *)&c_addr, &clen);
		//输出错误信息
		if(c_fd == -1)
		perror("Failed to establish connection!");
		//打印客户端IP地址
		printf("Get connect:%s\n",inet_ntoa(c_addr.sin_addr));
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
 * 2012/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void mainFunctionInit(void)
{
	/* 1.指令工厂初始化 */
	pcommandHead = addvoiceControlToCommand(pcommandHead);
	pcommandHead = addsocketControlToCommand(pcommandHead);

	/* 2.设备控制工厂初始化 */
	pdeviceHead = addequipment1ToDevices(pdeviceHead);
	pdeviceHead = addequipment2ToDevices(pdeviceHead);
	pdeviceHead = addfireAlarmToDevices(pdeviceHead);





	///* 3.1 语言线程 */
	//pthread_create(&voiceThread, NULL, voice_thread, NULL);
	//printf("voiceThread start success\n");

	///* 3.2 socket线程 */
	//pthread_create(&socketThread, NULL, socket_thread, NULL);
	//printf("socketThread start success\r\n");

	///* 等待线程退出 */
	//pthread_join(voiceThread, NULL);
	//pthread_join(socketThread, NULL);
}


/* --------------------------------------------------------------------------------
 * 设备功能控制
 * --------------------------------------------------------------------------------
 * 2012/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

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


}












