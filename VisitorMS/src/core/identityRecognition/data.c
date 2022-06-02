
/* 主程序数据处理源文件 */

#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "data.h"

#define DATABASE_NAME "user.db"
#define TABLE_USER "user"

pthread_mutex_t db_mutex;
sqlite3 *db;      //数据库

/* 添加一个用户 */
/* 客户端发送注册请求后，服务器端注册用户信息到数据库中 */
int db_add_user(char name[], char passwd[])
{
	char *errmsg;
	char sqlstr[1024] = {0};

	if ((name == NULL) || (passwd == NULL))
	{
		printf("Invalid name or password entered.\r\n");
		return -1;
	}
	if ((strlen(name) > 32) || (strlen(passwd) > 32))
	{
		printf("The entered name or password is too long.\r\n");
		return -1;
	}

	sprintf(sqlstr, "insert into %s values('%s', '%s',-1, 1,0)",
			TABLE_USER, name, passwd);

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0)
	{
		printf("Database query error: %s\r\n", sqlite3_errmsg(db));
	}
	else
	{
		//printf("User added successfully.\r\n");
	}
	//printf("\r\n");
	return 1;
}

/* 判断某个用户名是否注册 */
/*	功能：判断某个用户名是否注册
	返回值：有名字返回index，否则返回-1 */
int db_user_if_reg(char *name)
{
	int state = -1;
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select regist from %s where name='%s'",
			TABLE_USER, name);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("Database query error: %s\r\n", errmsg);
		sqlite3_free(errmsg);
	}
	index = ncolumn;
	
	if (nrow > 0)
	{
		//在数据库中找到指定名字的用户(数据)，至少有一条数据
		state = 1;
	}
	else
	{
		//在数据库中没有找到指定名字的用户(数据)
		state = -1;
	}
	sqlite3_free_table(result);
	return state;
}

/* 判断用户名密码是否正确 */
int db_user_pwd_corrct(char *name, char *passwd)
{
	int state = -1;
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select * from %s where name='%s' and passwd='%s'",
			TABLE_USER, name, passwd);

	/*功能：执行SQL操作
	  参数：  db：数据库句柄
	 		sql：SQL语句
			resultp：用来指向sql执行结果的指针
	 		nrow：满足条件的记录的数目
	 		ncolumn：每条记录包含的字段数目
			errmsg：错误信息指针的地址
	返回值：	成功返回0，失败返回错误码   	*/
	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("Database query error: %s\r\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	index = ncolumn;
	
	if (nrow > 0)
	{
		//在数据库中找到指定名字和密码的用户(数据)
		state = 1;
	}
	else
	{
		//在数据库中没有找到指定名字和密码的用户(数据)		
		state = -1;
	}
	sqlite3_free_table(result);
	return state;
}

/* 数据库初始化 */
int database_init()
{
	int n;
	int ret;
	char *errmsg;
	char sql[] =
		"CREATE TABLE IF NOT EXISTS user(name INT PRIMARY KEY 	NOT NULL,passwd	TEXT	NOT NULL,fd	INT NOT NULL,regist	INT	 NOT NULL,keygen INT);";

	pthread_mutex_init(&db_mutex, NULL);

	if (sqlite3_open(DATABASE_NAME, &db) < 0)
	{
		printf("Failed to open sqlite3: %s\r\n", sqlite3_errmsg(db));
		return -1;
	}

	/* 使用回调函数执行SQL语句 */
	ret = sqlite3_exec(db, sql, NULL, 0, &errmsg);

	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "Database query error: %s\r\n", errmsg);
		sqlite3_free(errmsg);
	}
	else
	{
		fprintf(stdout, "The database initialized successfully.\r\n");
	}
	return 0;
}

/* 关闭数据库 */
void database_close()
{
	sqlite3_close(db);
}

