
/* 控制工厂 */

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>

struct controlDevice {
	char deviceName[128];
	int deviceStatus;
	int pinNum;  // 管脚号

	int (*open)(int pinNum);
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum);
	
	int (*readStatus)(int pinNum);
	int (*changeStatus)(int status);

	struct controlDevice *next;
};

/* 将设备注册到链表的函数声明 */
struct controlDevice *addBathroomLightToDevices(struct controlDevice *phead);
struct controlDevice *addlivingroomLightToDevices(struct controlDevice *phead);
struct controlDevice *addrestaurantLightToDevices(struct controlDevice *phead);
struct controlDevice *addfireAlarmToDevices(struct controlDevice *phead);
























