
/* 识别工厂 */

#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <wiringSerial.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

/* 通过宏定义来替代数字，代码更加规范 */
#define VISITOR			 20
#define USER1  			 21
#define USER2            22
#define ADMINISTRATORS   23


/* 识别工厂结构体 */
struct identityRecognition {
	int userIdentity;                      // 用户身份
	char identityName[32];                 // 此识别方法的名称，用于链表查找
	char userPassword[32];                 // 存储用户输入的密码
	void (*initRecognition)(struct identityRecognition *bodyRecognition);   // 识别初始化函数
	int flagRecognition;                   // 识别标志位，判断是否验证通过，0-失败，1-通过

	struct identityRecognition *next;
};


/* 将设备注册到链表的函数声明 */
struct identityRecognition *addAppRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addPasswordRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addVoiceRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addFaceRecognitionToList(struct identityRecognition *phead);

















