
/* 数据库处理源代码 */
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
	printf("Please enter the user password:\r\n");
	scanf("%s", userMsg.passwd);
	getchar();  //用于吸收回车

	/* 查询用户是否注册 */
	int dest_index;  
	dest_index = db_user_if_reg(userMsg.name);
	if (dest_index == -1)
	{
		printf("The user you entered does not exist.\r\n");
		return FALSE;
	}
	
	/* 检查输入的密码是否正确 */
	int ret;
	ret = db_user_pwd_corrct(userMsg.name, userMsg.passwd);
	
	if (ret == -2)
	{
		//密码不正确
		printf("The password you entered is incorrect.\r\n");
		return FALSE;
	}
	else if (ret == -1)
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
	printf("Please enter the password you want to set:\r\n");
	scanf("%s", userMsg.passwd);
	getchar();  //用于吸收回车

	/* 查询用户是否注册 */
	int dest_index;  
	dest_index = db_user_if_reg(userMsg.name);
	if (dest_index != -1)
	{
		printf("The name you entered already exists.\r\n");
		return FALSE;
	}
	
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


















