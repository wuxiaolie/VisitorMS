#include "mainPro.h"



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
