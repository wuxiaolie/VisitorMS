
#include "menu.h"

/* 初始化ncurse库 */
void initNcurse() 
{
    initscr();
    keypad(stdscr, 1);
    noecho();            // 输入的字符不在界面上显示
}

/* 身份验证失败提示界面 */
void picOfIdentityError(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("\n");
	printw("                        Authentication failed.                       \n");
	printw("-------------------------Please verify again!------------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();
}

/* 输入错误提示界面 */
void picOfInputError(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("         The number entered does not meet the requirements.          \n");
	printw("    The input is invalid or the selected function is unavailable.    \n");
	printw("-------------------------Please re-enter it!-------------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();
}

/* 选择登录身份界面 */
void picOfSelectIdentity(void)
{	
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("-----------Please enter the number to select your identity-----------\n");
	printw("\n");
	printw("\t\t| 1. Visitor                               \t\t\n");
	printw("\t\t| 2. User1                                 \t\t\n");
	printw("\t\t| 3. User2                                 \t\t\n");
	printw("\t\t| 4. Administrators                        \t\t\n");
	printw("\t\t| 5. Other users                           \t\t\n");
	printw("\n");
	printw("-------------------Enter q to return to log off----------------------\n");
	refresh();
}

/* 选择登录身份界面-输入错误重新提示 */
void picOfSelectIdentityPro(void)
{	
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("The number entered does not meet the requirements.Please re-enter it!\n");
	printw("\n");
	printw("\t\t| 1. Visitor                               \t\t\n");
	printw("\t\t| 2. User1                                 \t\t\n");
	printw("\t\t| 3. User2                                 \t\t\n");
	printw("\t\t| 4. Administrators                        \t\t\n");
	printw("\t\t| 5. Other users                           \t\t\n");
	printw("\n");
	printw("-------------------Enter q to return to log off----------------------\n");
}

/* 身份验证界面 */
void picOfAuthenticationInterface(void)
{	
	move(0, 0);
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
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
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
	printw("--------------Enter q to return to the previous level----------------\n");
}

/* 功能选择界面-访客 */
void picOfFunctionSelect_visitor(void)
{
	move(0, 0);
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
	printw("\n");
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment II                          \t\t\n");
	printw("\t\t| 3. Camera                                \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
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
	printw("\n");
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment III                         \t\t\n");
	printw("\t\t| 3. Camera                                \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* 功能选择界面-管理员 */
void picOfFunctionSelect_administrators(void)
{
	move(0, 0);
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
	printw("\n");
	printw("\t\t            | 1. Fool                      \t\t\n");
	printw("\t\t            | 2. Simple                    \t\t\n");	
	printw("\t\t            | 3. Hard                      \t\t\n");
	printw("\t\t            | 4. Hell                      \t\t\n");
	printw("\t\t            | 5. Auto                      \t\t\n");
	printw("\n");
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
	refresh();
}















