#include "controlDevice.h"
#include "inputCommand.h"

/* 定义全局变量 */
struct controlDevice *pdeviceHead = NULL;
struct inputCommand *pcommandHead = NULL;
struct inputCommand *socketHead = NULL;
int c_fd;

/* 定义mainFunctionProgram函数需要的变量 */
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
 * 功能描述： 主要功能实现
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2012/05/18	V1.0   杨皓清	        创建
 ***********************************************************************/
void mainFunctionProgram(void)
{

	/* 1.指令工厂初始化 */
	pcommandHead = addvoiceControlToCommand(pcommandHead);
	pcommandHead = addsocketControlToCommand(pcommandHead);

	/* 2.设备控制工厂初始化 */
	pdeviceHead = addBathroomLightToDevices(pdeviceHead);
	pdeviceHead = addlivingroomLightToDevices(pdeviceHead);
	pdeviceHead = addrestaurantLightToDevices(pdeviceHead);
	pdeviceHead = addfireAlarmToDevices(pdeviceHead);

	/* 3.线程池建立 */
	/* 3.1 语言线程 */
	pthread_create(&voiceThread, NULL, voice_thread, NULL);
	printf("voiceThread start success\n");

	/* 3.2 socket线程 */
	pthread_create(&socketThread, NULL, socket_thread, NULL);
	printf("socketThread start success\r\n");

	/* 3.3 摄像头线程 */
	
	/* 3.4 火灾报警线程 */

	/* 等待线程退出 */
	pthread_join(voiceThread, NULL);
	pthread_join(socketThread, NULL);
}


