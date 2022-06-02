#include "controlDevice.h"
#include "inputCommand.h"

struct controlDevice *pdeviceHead = NULL;
struct inputCommand *pcommandHead = NULL;
struct inputCommand *socketHead = NULL;

int c_fd;


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


int main()
{
	char name[128];
	pthread_t voiceThread;	
	pthread_t socketThread;
	struct controlDevice *tmp = NULL;
	
	if (wiringPiSetup() == -1) {
		printf("wiringPiSetup error\n");
		return -1;
	}
	

	//1.指令工厂初始化
	pcommandHead = addvoiceControlToCommand(pcommandHead);
	pcommandHead = addsocketControlToCommand(pcommandHead);
	//2.设备控制工厂初始化
	pdeviceHead = addBathroomLightToDevices(pdeviceHead);
	pdeviceHead = addlivingroomLightToDevices(pdeviceHead);
	pdeviceHead = addrestaurantLightToDevices(pdeviceHead);
	pdeviceHead = addfireAlarmToDevices(pdeviceHead);
	//3.线程池建立
	//3.1 语言线程
	pthread_create(&voiceThread, NULL, voice_thread, NULL);
	printf("voiceThread start success\n");
	//3.2 socket线程
	pthread_create(&socketThread, NULL, socket_thread, NULL);
	printf("socketThread start success\r\n");
	//3.3 摄像头线程
	
	//3.4 火灾报警线程

	//等待线程退出
	pthread_join(voiceThread, NULL);
	pthread_join(socketThread, NULL);
}
