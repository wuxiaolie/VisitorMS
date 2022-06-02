
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/* 初始化ncurse库 */
void initNcurse(); 

/* --------------------------------------------------------------------------------
 * 设备功能界面
 * --------------------------------------------------------------------------------
 * 2012/05/21	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 设备功能选择界面 */
void picOfEquipmentFunctionSelect(void);

/* 摄像头使用提示界面 */
void picOfCameraFunctionSelect(void);












/* --------------------------------------------------------------------------------
 * 系统功能界面
 * --------------------------------------------------------------------------------
 * 2012/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 身份验证失败提示界面 */
void picOfIdentityError(void);

/* 输入错误提示界面 */
void picOfInputError(void);

/* 选择登录身份界面 */
void picOfSelectIdentity(void);

/* 选择登录身份界面-输入错误重新提示 */
void picOfSelectIdentityPro(void);

/* 功能选择界面-访客 */
void picOfFunctionSelect_visitor(void);

/* 功能选择界面-用户1 */
void picOfFunctionSelect_user1(void);

/* 功能选择界面-用户2 */
void picOfFunctionSelect_user2(void);

/* 功能选择界面-管理员 */
void picOfFunctionSelect_administrators(void);

/* 身份验证界面 */
void picOfAuthenticationInterface(void);

/* 身份验证界面-输入错误重新提示 */
void picOfAuthenticationInterfacePro(void);

/* 贪吃蛇游戏界面 */
void picOfSnakeGame(void);

/* 清屏 */
void picRefresh(void); 



