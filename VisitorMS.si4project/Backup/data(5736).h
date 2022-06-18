
/* 主程序数据处理头文件 */

/* 在线用户结构体 */
struct ONLINE_USER
{
	int fd;	   			//-1
	int flage; 			// registed or not
	char name[32];
	char passwd[32];
};

/* 添加一个用户 */
/* 客户端发送注册请求后，服务器端注册用户信息到数据库中 */
int db_add_user(char name[], char passwd[]);

/* 判断某个用户名是否注册 */
/*	功能：判断某个用户名是否注册
	返回值：有名字返回index，否则返回-1 */
int db_user_if_reg(char *name);

/* 判断用户名密码是否正确 */
int db_user_pwd_corrct(char *name, char *passwd);

/* 数据库初始化 */
int database_init();

/* 关闭数据库 */
void database_close();























