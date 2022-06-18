
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

/* 密码验证源代码 */
/* 参考chat聊天室server程序 */

#include "identityRecognition.h"
#include "data.h"

/* 密码识别 */
int passwordRecognitionMain(int numOfIdentity)
{
	/* 定义一个用户结构体 */
	struct ONLINE_USER userMsg;

	/* 初始化数据库 */
	if (database_init() < 0)
	{
		printf("Database initialization failed.\r\n");
		return FALSE;
	}

	/* 接收用户输入 */
	printf("Please enter the user name:\r\n");
	scanf("%s", userMsg.name);
	getchar();  //用于吸收回车

	/* 查询用户是否注册 */
	int dest_index;  
	dest_index = db_user_if_reg(userMsg.name);
	if (dest_index == -1)
	{
		printf("The user you entered does not exist.\r\n");
		return FALSE;
	}
	
	printf("Please enter the user password:\r\n");
	scanf("%s", userMsg.passwd);
	getchar();  //用于吸收回车
	
	/* 检查输入的密码是否正确 */
	int ret;
	ret = db_user_pwd_corrct(userMsg.name, userMsg.passwd);
	
	if (ret == -1)
	{
		//密码不正确
		printf("The password you entered is incorrect.\r\n");
		return FALSE;
	}
	else if (ret == 1)
	{
		//密码正确，允许登录
		printf("User %s login succeeded.\r\n", userMsg.name);
		return TRUE;
	}
	else
	{
		printf("User %s login failed.\r\n", userMsg.name);
		return FALSE;
	}

	/* 关闭数据库 */
	database_close();
	return FALSE;
}

/* 注册用户 */
int registeredUserMain()
{
	/* 定义一个用户结构体 */
	struct ONLINE_USER userMsg;

	/* 初始化数据库 */
	if (database_init() < 0)
	{
		printf("Database initialization failed.\r\n");
		return FALSE;
	}
	
	/* 接收用户输入 */
	printf("Please enter the name you want to set:\r\n");
	scanf("%s", userMsg.name);
	getchar();  //用于吸收回车

	/* 查询用户是否注册 */
	int dest_index;  
	dest_index = db_user_if_reg(userMsg.name);
	if (dest_index != -1)
	{
		printf("The name you entered already exists.\r\n");
		return FALSE;
	}

	printf("Please enter the password you want to set:\r\n");
	scanf("%s", userMsg.passwd);
	getchar();  //用于吸收回车
	
	/* 进行注册，插入到数据库中 */
	int ret;
	ret = db_add_user(userMsg.name, userMsg.passwd);
	if (ret == -1)
	{
		//注册失败
		printf("User addition failed.\r\n");
		return FALSE;
	}
	else if (ret == 1)
	{
		//注册成功
		printf("User added successfully.\r\n");
		return TRUE;
	}
	
	/* 关闭数据库 */
	database_close();
	return FALSE;
}


















