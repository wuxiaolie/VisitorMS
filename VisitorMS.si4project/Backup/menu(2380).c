
#include "menu.h"

/* 初始化ncurse库 */
void initNcurse() 
{
    initscr();
    keypad(stdscr, 1);
    noecho();            // 输入的字符不在界面上显示
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
	printw("\n");
	printw("\t\t| 1. Open equipment                        \t\t\n");
	printw("\t\t| 2. Close equipment                       \t\t\n");
	printw("\t\t| 3. Read equipment status                 \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
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
	printw("\n");
	printw("\t\t| 1. Open camera                           \t\t\n");
	printw("\t\t| 2. Close camera                          \t\t\n");
	printw("\t\t| 3. Under development                     \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
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
	printw("\n");
	printw("\t\t| 1. Download log                          \t\t\n");
	printw("\t\t| 2. Upload log                            \t\t\n");
	printw("\t\t| 3. View log                              \t\t\n");
	printw("\t\t| 4. Turn off the function                 \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("--------------Enter q to return to the previous level----------------\n");
	refresh();
}

/* --------------------------------------------------------------------------------
 * 识别功能界面
 * --------------------------------------------------------------------------------
 * 2022/05/23	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 忘记密码提示界面 */
void picOfForgetPassword(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("                     If you forget your password                     \n");
	printw("Please contact the background customer service to reset your password\n");
	printw("-----------------------E-mail: 970407688@qq.com----------------------\n");
	printw("                       Enter any key to return.                      \n");
	printw("\n");
	printw("\n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();
}

/* --------------------------------------------------------------------------------
 * 指令控制界面
 * --------------------------------------------------------------------------------
 * 2022/05/20	V1.0   杨皓清	        创建
 ---------------------------------------------------------------------------------- */

/* 语言控制提示界面 */
void picOfVoiceControl(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------The voice control is turned on until you exit the user-------\n");
	printw("------Please say your instructions to select the function you want---\n");
	printw("\n");
	printw("\t\t| 1. Open the equipment                    \t\t\n");
	printw("\t\t| 2. Close the equipment                   \t\t\n");
	printw("\t\t| 3. Under development                     \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
	printw("------------------------Enter any key to return----------------------\n");
	refresh();
}

/* 网络控制提示界面 */
void picOfSocketControl(void)
{
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("--------The socket control is turned on until you exit the user------\n");
	printw("---Please submit your instructions to select the function you want---\n");
	printw("\n");
	printw("\t\t| 1. Open the equipment                    \t\t\n");
	printw("\t\t| 2. Close the equipment                   \t\t\n");
	printw("\t\t| 3. Under development                     \t\t\n");
	printw("\t\t| 4. Under development                     \t\t\n");
	printw("\t\t| 5. Under development                     \t\t\n");
	printw("\n");
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
	printw("\t\t| 3. Voice recognition                     \t\t\n");
	printw("\t\t| 4. Mobile phone verification             \t\t\n");
	printw("\t\t| 5. Forget password                       \t\t\n");
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
	printw("\t\t| 3. Voice recognition                     \t\t\n");
	printw("\t\t| 4. Mobile phone verification             \t\t\n");
	printw("\t\t| 5. Forget password                       \t\t\n");
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
	printw("\t\t| 3. Fire-alarm                            \t\t\n");
	printw("\t\t| 4. Turn on voice control                 \t\t\n");
	printw("\t\t| 5. Turn on network control               \t\t\n");
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
	printw("\t\t| 2. Fire-alarm                            \t\t\n");
	printw("\t\t| 3. Camera                                \t\t\n");
	printw("\t\t| 4. Turn on voice control                 \t\t\n");
	printw("\t\t| 5. Turn on network control               \t\t\n");
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
	printw("\t\t| 1. Equipment I                           \t\t\n");
	printw("\t\t| 2. Equipment II                          \t\t\n");	
	printw("\t\t| 3. Fire-alarm                            \t\t\n");
	printw("\t\t| 4. Camera                                \t\t\n");
	printw("\t\t| 5. Upload and download log               \t\t\n");
	printw("\t\t| 6. Turn on voice control                 \t\t\n");
	printw("\t\t| 7. Turn on network control               \t\t\n");
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
	printw("\n");
	refresh();
}















