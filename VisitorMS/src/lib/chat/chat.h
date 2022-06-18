
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

/* 客户端与服务器共用头文件 */

#ifndef _TCP_CHAT
#define _TCP_CHAT

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
//#define  __DEBUG 1
//#define PRINTF         // 服务端打印信息开关

#define MAX_USER_NAME_LEN 32 
#define MAX_USER_NUM 64
#define SERVER_PORT 8888   // 通讯端口号

/* 在线用户结构体 */
struct ONLINE_USER
{
	int fd;	   			//-1
	int flage; 			// registed or not
	char name[32];
	char passwd[32];
};

/* C/S通信的结构体 */
struct protocol
{
	int cmd;
	int state;			 // keygen 或者 指令状态
	char name[32];
	char data[64];
};

struct enc_data
{
	unsigned int sync;
	struct protocol data;
};

/* cmd */
#define BROADCAST 0X00000001
#define PRIVATE 0X00000002
#define REGISTE 0X00000004
#define LOGIN 0X00000008
#define ONLINEUSER 0X00000010
#define LOGOUT 0X00000020
#define KEYGEN 0X00000040

/* return code */
#define OP_OK 0X80000000
#define ONLINEUSER_OK 0X80000001
#define ONLINEUSER_OVER 0X80000002
#define NAME_EXIST 0X80000003
#define NAME_PWD_NMATCH 0X80000004
#define USER_LOGED 0X80000005
#define USER_NOT_REGIST 0X80000006

#endif
