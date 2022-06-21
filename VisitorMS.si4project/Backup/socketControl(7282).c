
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
	.IP = "192.168.43.183",
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


