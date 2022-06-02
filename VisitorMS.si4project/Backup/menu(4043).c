
#include "menu.h"

/* 初始化ncurse库 */
void initNcurse() 
{
    initscr();
    keypad(stdscr, 1);
    noecho();
}

/* 身份验证界面 */
void picOfAuthenticationInterface(void)
{	
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--Please enter the number to select the login authentication method--\n");
	printw("\n");
	printw("\t\t| 1. Password login                        \t\t\n");
	printw("\t\t| 2. Face recognition                      \t\t\n");
	printw("\t\t| 3. Password recognition                  \t\t\n");
	printw("\t\t| 4. Mobile phone verification             \t\t\n");
	printw("\t\t| 5. Visitor login                         \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
}

/* 身份验证界面-输入错误重新提示 */
void picOfAuthenticationInterfacePro(void)
{	
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("The number entered does not meet the requirements.Please re-enter it!\n");
	printw("\n");
	printw("\t\t| 1. Password login                        \t\t\n");
	printw("\t\t| 2. Face recognition                      \t\t\n");
	printw("\t\t| 3. Password recognition                  \t\t\n");
	printw("\t\t| 4. Mobile phone verification             \t\t\n");
	printw("\t\t| 5. Visitor login                         \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
}

/* 功能选择界面-访客 */
void picOfFunctionSelect_visitor(void)
{
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("---------Please enter a number to select the function to use---------\n");
	printw("\n");
	printw("\t\t| 1. Snake game                            \t\t\n");
	printw("\t\t| 2. Under development                     \t\t\n");
	printw("\t\t| 3. Under development                     \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");	
}

/* 功能选择界面-用户1 */
void picOfFunctionSelect_user1(void)
{
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("\n");
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment II                          \t\t\n");
	printw("\t\t| 3. Camera                                \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");	

}

/* 功能选择界面-用户2 */
void picOfFunctionSelect_user2(void)
{
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("\n");
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment III                         \t\t\n");
	printw("\t\t| 3. Camera                                \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");	

}

/* 功能选择界面-管理员 */
void picOfFunctionSelect_administrators(void)
{
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("------Please enter a number to select the control device to use------\n");
	printw("\n");
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment II                          \t\t\n");	
	printw("\t\t| 3. Equipment III                         \t\t\n");
	printw("\t\t| 4. Camera                                \t\t\n");
	printw("\t\t| 5. Download log                          \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");	
}

/* 贪吃蛇游戏界面 */
void picOfSnakeGame(void)
{
	printw("======================= Welcome to Snake Eating =====================\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------------------Please select difficulty level-------------------\n");
	printw("\n");
	printw("\t\t               | 1. Fool                   \t\t\n");
	printw("\t\t               | 2. Simple                 \t\t\n");	
	printw("\t\t               | 3. Hard                   \t\t\n");
	printw("\t\t               | 4. Hell                   \t\t\n");
	printw("\t\t               | 5. Auto                   \t\t\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");	
}

/* 刷新界面 */
void picRefresh(void) 
{
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
}















