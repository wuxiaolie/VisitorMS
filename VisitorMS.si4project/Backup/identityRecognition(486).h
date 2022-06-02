
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

struct identityRecognition {


	struct identityRecognition *next;
};

/* 将设备注册到链表的函数声明 */
struct identityRecognition *addAppRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addPasswordRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addVoiceRecognitionToList(struct identityRecognition *phead);
struct identityRecognition *addFaceRecognitionToList(struct identityRecognition *phead);














