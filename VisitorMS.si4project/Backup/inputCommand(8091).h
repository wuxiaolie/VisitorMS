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

/* 指令工厂 */



struct inputCommand {
	char commandName[128];
	char deviceName[128];
	char commandID[32];
	void (*initCommand)(struct inputCommand *voiceDevice, char *ipAdress, char *port);
	int (*getCommand)(struct inputCommand *voiceDevice);
	char log[1024];
	char port[12];
	char IP[32];
	int sfd;
	int fd;

	struct inputCommand *next;
};

struct inputCommand *addvoiceControlToCommand(struct inputCommand *phead);
struct inputCommand *addsocketControlToCommand(struct inputCommand *phead);














