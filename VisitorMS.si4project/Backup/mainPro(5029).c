
#include "mainPro.h"

int main()
{	
	/* 定义mainFunctionProgram函数需要的变量 */
	char name[128];
	pthread_t voiceThread;	
	pthread_t socketThread;
	struct controlDevice *tmp = NULL;

	/* 初始化wiringPi库 */
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup error\n");
		return -1;
	}

	/* 调用函数显示起始界面 */









	return 0;	
}
