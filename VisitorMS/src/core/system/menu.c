
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
 
#include "menu.h"

/* 初始化ncurse库 */
void initNcurse() 
{
    initscr();
    keypad(stdscr, 1);
    noecho();            // 输入的字符不在界面上显示
}

/* --------------------------------------------------------------------------------
 * 身份识别提示界面
 * --------------------------------------------------------------------------------
 * 2022/05/25	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 注册用户提示界面 */
void picOfRegisteredUser(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("--Please enter the account and password you want to set as prompted--\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
}

/* 忘记密码提示界面 */
void picOfForgetPassword(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                     If you forget your password                     \n");
	printw("Please contact the background customer service to reset your password\n");
	printw("-----------------------E-mail: 970407688@qq.com----------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* 人脸识别提示界面 */
void picOfFaceRecognition(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                    Please provide your face photo                   \n");
	printw("              Please put your photo in the \\src\\tmp folder           \n");
	printw("-------------------------Name it \"photo\" jpg-------------------------\n");
	printw("                      Enter any key to continue.                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* 口令识别提示界面 */
void picOfVoiceRecognition(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("     Please speak the identification password into the microphone    \n");
	printw("---------------------For example, say \"open sesame\"------------------\n");
	printw("                        Enter any key to start.                      \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* APP识别提示界面 */
void picOfAppRecognition(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("-------------The App identification function is turned on!-----------\n");
	printw("-------Please open your mobile phone and click the login button------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
}

/* 密码识别提示界面 */
void picOfPasswordRecognition(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("----------Please enter your account and password as prompted---------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
}

/* --------------------------------------------------------------------------------
 * 设备功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 设备功能选择界面 */
void picOfEquipmentFunctionSelect(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function you want-------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                     | 1. Open equipment                             \n");
	printw("                     | 2. Close equipment                            \n");
	printw("                     | 3. Read equipment status                      \n");
	printw("                     | 4. Under development                          \n");
	printw("                     | 5. Under development                          \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 摄像头使用提示界面 */
void picOfCameraFunctionSelect(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function you want-------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                    | 1. Open camera                                 \n");
	printw("                    | 2. Close camera                                \n");
	printw("                    | 3. Under development                           \n");
	printw("                    | 4. Under development                           \n");
	printw("                    | 5. Under development                           \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* ftp使用提示界面 */
void picOfFtpFunctionSelect(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function you want-------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                   | 1. Download log                                 \n");
	printw("                   | 2. Upload log                                   \n");
	printw("                   | 3. View log                                     \n");
	printw("                   | 4. Turn off the function                        \n");
	printw("                   | 5. Under development                            \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 聊天室使用提示界面 */
void picOfChatRoomFunction(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("-------The chat room server has been started in the background!------\n");
	printw("-------------------The chat room client is starting!-----------------\n");
	printw("----Other users log in, please connect through the client program----\n");
	printw("------------./client SERVERIP 8888 & ./client 127.0.0.1 8888---------\n");
	printw("------------The steps for using the chat room are as follows-------- \n");
	printw("																	 \n");
	printw("                   1. Log in to your account again                   \n");
	printw("                   2. Choose public & private chat                   \n");
	printw("                   3. Have a nice chat                               \n");
	printw("																	 \n");
	printw("																	 \n");	
	printw("----------------Enter ctrl + c to turn off the chat room-------------\n");
	printw("----------------------Enter any key to to continue-------------------\n");
	refresh(); 
	getch();
}

/* 聊天室退出提示界面 */
void picOfChatRoomEnd(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	printw("------------------The chat room server close seccess!----------------\n");
	printw("------------------The chat room client close seccess!----------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* --------------------------------------------------------------------------------
 * 指令控制界面
 * --------------------------------------------------------------------------------
 * 2022/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 网络控制提示界面 */
void picOfSocketControl(void)
{
	picRefresh();    //刷新一下界面，把语音可能打印的信息去除

	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------Please use the client to connect to 192.168.3.143 8010-------\n");
	printw("--------The socket control is turned on until you exit the user------\n");
	printw("---Please submit your instructions to select the function you want---\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                   | open1  - Open  equipment  1                     \n");
	printw("                   | close1 - Close equipment  1                     \n");
	printw("                   | open2  - Open  equipment  2                     \n");
	printw("                   | close2 - Close equipment  2                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("------------------------Enter any key to return----------------------\n");
	refresh();
}

/* 语音控制提示界面 */
void picOfVoiceControl(void)
{
	picRefresh();    //刷新一下界面，把网络可能打印的信息去除

	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------Please speak Chinese instructions into the microphone--------\n");
	printw("--------The voice control is turned on until you exit the user-------\n");
	printw("------Please say your instructions to select the function you want---\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | chinese - Open  equipment  1                     \n");
	printw("                  | chinese - Close equipment  1                     \n");
	printw("                  | chinese - Open  equipment  2                     \n");
	printw("                  | chinese - Close equipment  2                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("------------------------Enter any key to return----------------------\n");
	refresh();
}

/* 串口控制提示界面 */
void picOfUsartControl(void)
{
	picRefresh();    //刷新一下界面，把网络可能打印的信息去除

	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------Please send your instructions through the serial port--------\n");
	printw("--------The usart control is turned on until you exit the user-------\n");
	printw("---Please submit your instructions to select the function you want---\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                 | open1  - Open  equipment  1                       \n");
	printw("                 | close1 - Close equipment  1                       \n");
	printw("                 | open2  - Open  equipment  2                       \n");
	printw("                 | close2 - Close equipment  2                       \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("------------------------Enter any key to return----------------------\n");
	refresh();
}

/* --------------------------------------------------------------------------------
 * 系统功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 身份验证失败提示界面 */
void picOfIdentityError(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("                        Authentication failed.                       \n");
	printw("-------------------------Please verify again!------------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* 输入错误提示界面 */
void picOfInputError(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("         The number entered does not meet the requirements.          \n");
	printw("    The input is invalid or the selected function is unavailable.    \n");
	printw("-------------------------Please re-enter it!-------------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getch();
}

/* 选择登录身份界面 */
void picOfSelectIdentity(void)
{	
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------Please enter the number to select your identity-----------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Visitor                                       \n");
	printw("                  | 2. User1                                         \n");
	printw("                  | 3. User2                                         \n");
	printw("                  | 4. Administrators                                \n");
	printw("                  | 5. Other users                                   \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("-------------------Enter q to return to log off----------------------\n");
	refresh();
}

/* 选择登录身份界面-输入错误重新提示 - 已废弃 */
void picOfSelectIdentityPro(void)
{	
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("The number entered does not meet the requirements.Please re-enter it!\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Visitor                                       \n");
	printw("                  | 2. User1                                         \n");
	printw("                  | 3. User2                                         \n");
	printw("                  | 4. Administrators                                \n");
	printw("                  | 5. Other users                                   \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("-------------------Enter q to return to log off----------------------\n");
	refresh();
	getch();
}

/* 身份验证界面 */
void picOfAuthenticationInterface(void)
{	
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--Please enter the number to select the login authentication method--\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Account and password login                    \n");
	printw("                  | 2. Face recognition                              \n");
	printw("                  | 3. Voice recognition                             \n");
	printw("                  | 4. Mobile app verification                       \n");
	printw("                  | 5. Forget password                               \n");
	printw("														       		 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 身份验证界面-输入错误重新提示 - 已废弃 */
void picOfAuthenticationInterfacePro(void)
{	
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("The number entered does not meet the requirements.Please re-enter it!\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Account and password login                    \n");
	printw("                  | 2. Face recognition                              \n");
	printw("                  | 3. Voice recognition                             \n");
	printw("                  | 4. Mobile app verification                       \n");
	printw("                  | 5. Forget password                               \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
	getch();
}

/* 功能选择界面-访客 */
void picOfFunctionSelect_visitor(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function to use---------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Registered user                               \n");
	printw("                  | 2. Snake game                                    \n");
	printw("                  | 3. Chat room                                     \n");
	printw("                  | 4. Under development                             \n");
	printw("                  | 5. Under development                             \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 功能选择界面-其他用户 */
void picOfFunctionSelect_otherusers(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function to use---------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                  | 1. Snake game                                    \n");
	printw("                  | 2. Chat room                                     \n");
	printw("                  | 3. Under development                             \n");
	printw("                  | 4. Under development                             \n");
	printw("                  | 5. Under development                             \n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 功能选择界面-用户1 */
void picOfFunctionSelect_user1(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("              | 1. Equipment I                                       \n");
	printw("              | 2. Equipment II                                      \n");
	printw("              | 3. Fire-alarm                                        \n");
	printw("              | 4. Turn on voice control                             \n");
	printw("              | 5. Turn on usart control                             \n");
	printw("              | 6. Turn on network control                           \n");
	printw("              | 7. Chat room                                         \n");
	printw("              | other key - Refresh net & usart & voice control      \n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 功能选择界面-用户2 */
void picOfFunctionSelect_user2(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("                                                                     \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("              | 1. Equipment I                                       \n");
	printw("              | 2. Fire-alarm                                        \n");
	printw("              | 3. Camera                                            \n");
	printw("              | 4. Turn on voice control                             \n");
	printw("              | 5. Turn on usart control                             \n");
	printw("              | 6. Turn on network control                           \n");
	printw("              | 7. Chat room                                         \n");
	printw("              | other key - Refresh net & usart & voice control      \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 功能选择界面-管理员 */
void picOfFunctionSelect_administrators(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("																	 \n");
	printw("              | 1. Equipment I                                       \n");
	printw("              | 2. Equipment II                                      \n");	
	printw("              | 3. Fire-alarm                                        \n");
	printw("              | 4. Camera                                            \n");
	printw("              | 5. Upload and download log                           \n");
	printw("              | 6. Turn on voice control                             \n");
	printw("              | 7. Turn on usart control                             \n");
	printw("              | 8. Turn on network control                           \n");
	printw("              | 9. Chat room                                         \n");
	printw("              | other key - Refresh net & usart & voice control      \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 贪吃蛇游戏界面 */
void picOfSnakeGame(void)
{
	move(0, 0);
	printw("======================= Welcome to Snake Eating =====================\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------------------Please select difficulty level-------------------\n");
	printw("																	 \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("                       | 1. Fool                                     \n");
	printw("                       | 2. Simple                                   \n");	
	printw("                       | 3. Hard                                     \n");
	printw("                       | 4. Hell                                     \n");
	printw("                       | 5. Auto                                     \n");
	printw("															         \n");
	printw("																	 \n");
	printw("                                                                     \n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 刷新界面 */
void picRefresh(void) 
{
	move(0, 0);
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("\n");
	refresh();
}















