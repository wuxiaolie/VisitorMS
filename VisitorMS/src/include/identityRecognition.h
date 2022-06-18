
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
#define OTHERUSERS       24
/* 真与假，在wiringPi库中已经定义 */
//#define TRUE 1
//#define FALSE 0

/* --------------------------------------------------------------------------------
 * 注册用户函数声明
 * --------------------------------------------------------------------------------
 * 2022/05/30	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */
int registeredUserMain(void);

/* --------------------------------------------------------------------------------
 * 人脸识别函数声明
 * --------------------------------------------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */
int faceRecognitionMain(int numOfIdentity);

/* --------------------------------------------------------------------------------
 * 密码识别函数声明
 * --------------------------------------------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */
int passwordRecognitionMain(int numOfIdentity);

/* --------------------------------------------------------------------------------
 * APP识别函数声明
 * --------------------------------------------------------------------------------
 * 2022/05/24	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */
/* App验证 */
int AppRecognitionMain(int numOfIdentity);





