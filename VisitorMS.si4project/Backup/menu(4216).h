
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

/* 初始化ncurse库 */
void initNcurse(); 

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

/* 刷新界面 */
void picRefresh(void); 



