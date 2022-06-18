
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

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/* 初始化ncurse库 */
void initNcurse(); 

/* --------------------------------------------------------------------------------
 * 身份识别提示界面
 * --------------------------------------------------------------------------------
 * 2022/05/25	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 注册用户提示界面 */
void picOfRegisteredUser(void);

/* 忘记密码提示界面 */
void picOfForgetPassword(void);

/* 人脸识别提示界面 */
void picOfFaceRecognition(void);

/* 口令识别提示界面 */
void picOfVoiceRecognition(void);

/* APP识别提示界面 */
void picOfAppRecognition(void);

/* 密码识别提示界面 */
void picOfPasswordRecognition(void);

/* --------------------------------------------------------------------------------
 * 设备功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 设备功能选择界面 */
void picOfEquipmentFunctionSelect(void);

/* 摄像头使用提示界面 */
void picOfCameraFunctionSelect(void);

/* ftp使用提示界面 */
void picOfFtpFunctionSelect(void);

/* 聊天室使用提示界面 */
void picOfChatRoomFunction(void);

/* 聊天室退出提示界面 */
void picOfChatRoomEnd(void);

/* --------------------------------------------------------------------------------
 * 指令控制界面
 * --------------------------------------------------------------------------------
 * 2022/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 语言控制提示界面 */
void picOfVoiceControl(void);

/* 网络控制提示界面 */
void picOfSocketControl(void);

/* 串口控制提示界面 */
void picOfUsartControl(void);

/* --------------------------------------------------------------------------------
 * 系统功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 身份验证失败提示界面 */
void picOfIdentityError(void);

/* 输入错误提示界面 */
void picOfInputError(void);

/* 选择登录身份界面 */
void picOfSelectIdentity(void);

/* 选择登录身份界面-输入错误重新提示 - 已废弃 */
void picOfSelectIdentityPro(void);

/* 功能选择界面-访客 */
void picOfFunctionSelect_visitor(void);

/* 功能选择界面-其他用户 */
void picOfFunctionSelect_otherusers(void);

/* 功能选择界面-用户1 */
void picOfFunctionSelect_user1(void);

/* 功能选择界面-用户2 */
void picOfFunctionSelect_user2(void);

/* 功能选择界面-管理员 */
void picOfFunctionSelect_administrators(void);

/* 身份验证界面 */
void picOfAuthenticationInterface(void);

/* 身份验证界面-输入错误重新提示 - 已废弃 */
void picOfAuthenticationInterfacePro(void);

/* 贪吃蛇游戏界面 */
void picOfSnakeGame(void);

/* 清屏 */
void picRefresh(void); 



