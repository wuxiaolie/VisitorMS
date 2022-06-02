
/* 控制工厂 */

#include <curses.h>
#include <wiringPi.h>
#include <stdio.h>
#include <string.h>

struct controlDevice {
	char deviceName[128];
	int deviceStatus;
	int pinNum;  // 管脚号

	int (*open)(struct controlDevice *equipmentNode);
	int (*close)(struct controlDevice *equipmentNode);
	int (*deviceInit)(struct controlDevice *equipmentNode);
	
	int (*readStatus)(struct controlDevice *equipmentNode);
	int (*changeStatus)(struct controlDevice *equipmentNode);

	struct controlDevice *next;
};

/* 将设备注册到链表的函数声明 */
struct controlDevice *addequipment1ToDevices(struct controlDevice *phead);
struct controlDevice *addequipment2ToDevices(struct controlDevice *phead);
struct controlDevice *addfireAlarmToDevices(struct controlDevice *phead);
























