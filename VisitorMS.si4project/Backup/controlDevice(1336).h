#include <wiringPi.h>
#include <stdio.h>
#include <string.h>

/* 控制工厂 */

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

struct controlDevice *addBathroomLightToDevices(struct controlDevice *phead);
struct controlDevice *addlivingroomLightToDevices(struct controlDevice *phead);
struct controlDevice *addrestaurantLightToDevices(struct controlDevice *phead);
struct controlDevice *addfireAlarmToDevices(struct controlDevice *phead);
























