
/**********************************************************************************************
 *    :|x].              ?ObU:        +jfl           ?Zdr'                   '"I>>iI"'        
 *    n$$${             x@$$k;       n$$$Mi         [B$$$c               "-xZ*%$$$$$%*pX+     
 *    >8$$k`           j$$$C^       ]$$$$$Q.       `k$$$$8l            ~Y#$$%kQznnuY0qhk|     
 *     j$$$n          {@$$0'       .q$$$$$B<       ($$$$$$/          'uB$$p{:                 
 *     'm$$B+        +&$$b,        _@$$B$$$z      ;#$$8%$$Z.         +$$$M:                   
 *      !&$$b^      !*$$#!         C$$$\k$$M:    .Q$$@}X$$8!         ,w$$$bc|}-~<iI".         
 *       f$$$x     :k$$&+         _B$$p./$$$x    /$$$u +@$$x          '[YdW@$$$$$$$%oOr>      
 *       'w$$%~   ^w$$B}         `b$$@- "h$$Wl  _8$$O' 'p$$o"             ^:!><+](n0#$$@Z>    
 *        >8$$b^ 'L$$$\          x$$$C   )$$$C Io$$a;   ($$$t                       `[#$$*:   
 *         /$$$X.c$$$x          <8$$&l   .Z$$@\w$$%+    "a$$#;     ,]]"               p$$$>   
 *         .J$$@w$$$Y.         .O$$$n     >8$$$$$$t      \$$$J     0$$*\"         '!(p$$$u.   
 *          "d$$$$$Q'          >B$$%i      r$$$$$L.      ^a$$@{    _b$$$&qJvnnncCq#$$$&Q-     
 *           lh$$$Y'           [$$$U       `0$$@C^        {@$$a^    .+jQk&@$$$$$@&aOn[:       
 *            :\r]             '{x)^        .+}>           ?UJ).         ^:l>>>l:^.            
 *                                                                                           
 * Copyright (C) 2022 - 2023, HaoQing, <970407688@qq.com>.
 * <https://github.com/wuxiaolie/VisitorMS> & <https://gitee.com/yang-haoqing/visitor-ms.git>
 *
 * This software is licensed as described in the file COPYING, which you should have received 
 * as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell copies of 
 * the Software, and permit persons to whom the Software is furnished to do so, under 
 * the terms of the COPYING file.
 *
 *********************************************************************************************/

/* ??????man??????????????????????????????????????? */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* ??????????????????????????????????????????????????????????????? */
#define LS   0
#define GET  1
#define PWD  2
#define IFGO 3
#define LCD  4
#define LLS  5
#define CD   6
#define PUT  7
#define QUIT 8
#define DOFILE  9

/* ??????????????????????????????????????? */
struct Msg {
        int type;
        char data[1024];
        char secondBuf[128];
};

/* ???????????????????????? */
int get_cmd_type(char *cmd)
{
	if (!strcmp("ls", cmd))			return LS;
	if (!strcmp("quit", cmd))		return QUIT;
	if (!strcmp("pwd", cmd))		return PWD;
	if (strstr(cmd, "cd") != NULL)	return CD;
	if (strstr(cmd, "get") != NULL)	return GET;
	if (strstr(cmd, "put") != NULL)	return PUT;
	//??????????????????????????????100???????????????
	return 100; 
}

/* ??????????????? */
char *get_dir(char *cmsg)
{
	char *p;
	p = strtok(cmsg, " ");
    //??????????????????cmsg????????????NULL
	p = strtok(NULL, " ");
	return p;
}

/* ?????????????????? */
void msg_handler(struct Msg msg, int fd)
{
	char dataBuf[1024] = {0};
	char *file = NULL;
	int fdfile;  //???????????????
	
	//msg.data???????????????
	printf("The command requested by the client is:  %s\n", msg.data);
	//??????????????????????????????????????????
	int ret = get_cmd_type(msg.data);

	switch(ret)
	{
        /* ???????????????????????? */
		case LS:
        	msg.type = 0;
            FILE *r1 = popen(msg.data, "r");
            fread(msg.data, sizeof(msg.data), 1, r1);
            write(fd, &msg, sizeof(msg));
            break;
            
		/* ?????????????????? */
		case PWD:
			msg.type = 0;
            //??????fork()???????????????????????????????????????/bin/sh -c???????????????msg.data??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
			FILE *r2 = popen(msg.data, "r");
            //???????????????1???????????????????????????????????????sizeof(msg.data),???????????????????????????????????? ptr?????????????????????
			fread(msg.data, sizeof(msg.data), 1, r2);
            //????????????????????????????????????
			write(fd, &msg, sizeof(msg));
			break;
		
        /* ???????????? */
		case CD:
			msg.type = 1;
			//???????????????????????????????????????????????????
			char *dir = get_dir(msg.data);
			printf("Switched to directory:  %s\n", dir);
            //????????????????????????
			chdir(dir);
			break;
            
       	/* ?????????????????? */
		case GET:
            msg.type = DOFILE;  //?????????????????????????????????GET/PUT???????????????
			//??????????????????????????????????????????
			file = get_dir(msg.data);  //?????????????????????
			//???????????????????????????file??????????????????
			if (access(file, F_OK) == -1) {
				strcpy(msg.data, "The requested file does not exist!");
				write(fd, &msg, sizeof(msg));
			} else {
				fdfile = open(file, O_RDWR);  //????????????????????????????????????
				read(fdfile, dataBuf, sizeof(dataBuf));  //????????????????????????dataBuf
				close(fdfile);  //?????????????????????????????????????????????
				//??????????????????masg.data????????????????????????????????????
                strcpy(msg.data, dataBuf);
				write(fd, &msg, sizeof(msg));
			}
			break;
            
        /* ?????????????????? */
		case PUT:
            //????????????????????????????????????pathname????????????????????????????????????????????????0666?????????
			fdfile = open(get_dir(msg.data), O_RDWR | O_CREAT, 0666);
			write(fdfile, msg.secondBuf, strlen(msg.secondBuf));
			close(fdfile);
			break;
            
        /* ?????? */
		case QUIT:
			printf("The client has exited.\n");
			printf("--------------------------------------\n");
			exit(-1);	
	}
}

/* ??????????????????socket?????????*/
int main(int argc, char **argv)
{
	int s_fd;
	int c_fd;
	int n_read;
	char readBuf[128];

	struct sockaddr_in s_addr;  //???????????????????????????
	struct sockaddr_in c_addr;  //???????????????connect????????????????????????????????????
	struct Msg msg;  

    //???????????????????????????
	if(argc != 2) {
		printf("Unqualified parameters!\n");
		exit(-1);
	}
    
	//?????????????????????????????????????????????????????????0
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	memset(&c_addr, 0, sizeof(struct sockaddr_in));

	/* 1.socket?????????socket????????? */
    //??????TCP/IP???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1) {
		perror("Ask for socket error!");
		exit(-1);
	}
    
    /* 2.bind???????????????IP????????????????????????????????????????????????????????????????????????????????? */
	s_addr.sin_family = AF_INET;  //?????????TCP/IP?????????
	s_addr.sin_port = htons(atoi(argv[1]));  //????????????????????????????????????????????????????????????????????????int?????????htons????????????????????????????????????????????????
	//inet_aton(argv[1], &s_addr.sin_addr);  //???IP??????????????????????????????????????????????????????????????????
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //??????IP?????????IP

	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));

	/* 3.listen??????????????????????????????????????????????????????????????? */
	listen(s_fd, 15);  //s_fd???????????????????????????15

    int clen = sizeof(struct sockaddr_in);
	/* ??????????????????????????????????????????????????????fork?????????????????? */

	printf("Waiting for client connection ...\n");
	printf("--------------------------------------\n");
	while(1) {
        
        /* 4.accept???????????????????????????????????????????????????????????????????????? */
		c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen);
        //??????????????????
		if(c_fd == -1)
			perror("Failed to establish connection!");
        //???????????????IP??????
        printf("Client connection succeeded.\n");
		printf("The IP address of the client is:  %s\n",inet_ntoa(c_addr.sin_addr));
		printf("--------------------------------------\n");
		/* ????????????????????????????????????????????????????????????????????????????????????????????? */
        //fork()??????????????????????????????????????????????????????PID?????????????????????????????????0
        //fork()?????????????????????????????????-1?????????????????????????????????errno
        //if??????????????????????????????while??????????????????????????????4???
		if(fork() == 0)	{
			while(1) {
                //??????msg?????????
				memset(msg.data, 0, sizeof(msg.data));
				//????????????????????????????????????????????????msg?????????????????????????????????????????????
				n_read = read(c_fd, &msg, sizeof(msg));
               
				if(n_read == 0)	{
					printf("The client has exited.\n");
					printf("--------------------------------------\n");
					break;	
				}
				else if(n_read > 0)	{
					msg_handler(msg, c_fd);	 //??????????????????
				}				
			}
		}
	}
    
    /* ???????????????????????????????????? */
	close(c_fd);  
	close(s_fd);
	return 0;
}
