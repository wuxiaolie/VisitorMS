
#include "inputCommand.h"

int socketInit(struct inputCommand *socketMsg, char *ipAdress, char *port)
{
	int s_fd;
	struct sockaddr_in s_addr;  //定义服务器的套接字
	memset(&s_addr, 0, sizeof(struct sockaddr_in));

	/* 1.socket，申请socket描述符 */
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1) {
		perror("Ask for socket error ");
		//exit(-1);
	}
    
    /* 2.bind，将服务器IP地址和端口号与一个套接字进行绑定（将套接字与地址关联） */
	s_addr.sin_family = AF_INET; 
	s_addr.sin_port = htons(atoi(socketMsg->port));  
	inet_aton(socketMsg->IP, &s_addr.sin_addr);  
	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));

	/* 3.listen，让服务器进入监听状态，等待客户端连接请求 */
	listen(s_fd, 15);  //s_fd等待连接队列最大为15
   	socketMsg->sfd = s_fd;
	printf("Socket server is listening ...\r\n");

	return 0;
        
}

int socketGetCommand(struct inputCommand *socketMsg)
{

	return 0;				
}

struct inputCommand socketControl = {
	.commandName = "socket",
	.commandID = {'\0'},
	.IP = "192.168.3.143",
	.port = "8010",
	.initCommand = socketInit,
	.getCommand = socketGetCommand,
	.log = {'\0'},
	.next = NULL,
};


/* 头插法 */
struct inputCommand *addsocketControlToCommand(struct inputCommand *phead)
{
	if (phead == NULL) {
		return &socketControl;
	} else {
		socketControl.next = phead;
		phead = &socketControl;
	}
}


