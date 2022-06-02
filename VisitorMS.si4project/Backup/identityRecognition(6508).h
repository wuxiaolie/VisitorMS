
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
	int userIdentity;
	char userPassword[32];
	void (*initRecognition)(struct identityRecognition *bodyRecognition);
	int flagRecognition;

	struct identityRecognition *next;
};


/* 将设备注册到链表的函数声明 */
struct identityRecognition *addAppRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addPasswordRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addVoiceRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addFaceRecognitionToList(struct identityRecognition *phead);

















