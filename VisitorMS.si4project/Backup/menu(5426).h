
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
 * 识别功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/23	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 忘记密码提示界面 */
void picOfForgetPassword(void);

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



