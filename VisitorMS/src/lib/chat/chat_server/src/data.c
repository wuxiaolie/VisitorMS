
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

/* 服务器数据处理源文件 */

#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "../../chat.h"
#include "../include/data.h"

sqlite3 *db;      //数据库

#define DATABASE_NAME "user.db"
#define TABLE_USER "user"
pthread_mutex_t db_mutex;

/* 引入外部全局函数声明 */
extern int enc_send_srv(int fd, void *data, int len, int keygen);

/* 添加一个用户 */
/* 客户端发送注册请求后，服务器端注册用户信息到数据库中 */
int db_add_user(char name[], char passwd[])
{
	char *errmsg;
	char sqlstr[1024] = {0};

	if ((name == NULL) || (passwd == NULL))
	{
		perror("Invalid name or password entered\n");
		return -1;
	}
	if ((strlen(name) > 32) || (strlen(passwd) > 32))
	{
		perror("The entered name or password is too long\n");
		return -1;
	}

	sprintf(sqlstr, "insert into %s values('%s', '%s',-1, 1,0)",
			TABLE_USER, name, passwd);

#if __DEBUG
	printf("cmd: %s\n", sqlstr);
#endif

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0)
	{
		#if __PRINTF
		printf("An error occurred: %s\n", sqlite3_errmsg(db));
		#endif
	}
	else
	{
		#if __PRINTF
		printf("User added successfully.\n");
		#endif
	}
	#if __PRINTF
	printf("\n");
	#endif
	return 1;
}

/* 判断某个用户是否在线 */
/* 客户端发送登陆命令后，服务器通过该函数判断该用户是否已经登陆成功 */
/* 返回值 1： 在线
	  -1：不在线
	  -2：用户不存在      */
int db_user_if_online(char *name, char *passwd)
{
	int ret;
	int state = -1;
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select fd from %s where name='%s' and passwd='%s'",
			TABLE_USER, name, passwd);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	index = ncolumn;
	
#if __DEBUG
	printf("%s: ncolumn = %d, nrow = %d\n", __func__, ncolumn, nrow);
#endif

	if (nrow == 1)
	{
		//找到
		state = atoi(result[index]);
		if (state > 0)
		{
			ret = 1;
		}
		else
		{
			ret = -1;
		}
	}
	else
	{
		//没找到
		ret = -2;
	}
	sqlite3_free_table(result);
	return ret;
}

/* 判断某个用户名是否注册 */
/* 用户发送注册命令，服务器需要判断该用户名是否已经被注册过 */
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
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	index = ncolumn;
	
#if __DEBUG
	printf("ncolumn = %d, nrow = %d\n", ncolumn, nrow);
#endif

	if (nrow > 0)
	{
		//找到
		state = atoi(result[index]);
	}
	else
	{
		//没找到
		state = -1;
	}
	sqlite3_free_table(result);
	return state;
}

/* 判断用户名密码是否正确 */
/* 用户发送登陆命令，需要判断用户名密码是否正确 */
/* select *from student where name='一口' and sage=19; */
int db_user_pwd_corrct(char *name, char *passwd)
{
	int state = -1;
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select * from %s where name='%s' and passwd='%s'",
			TABLE_USER, name, passwd);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	index = ncolumn;
	
#if __DEBUG
	printf("ncolumn = %d, nrow = %d\n", ncolumn, nrow);
#endif

	if (nrow > 0)
	{
		//找到
		state = 1;
	}
	else
	{
		//没找到
		state = -1;
	}
	sqlite3_free_table(result);
	return state;
}

/* 更新keygen */
int db_update_keygen(char *name, int keygen)
{
	int value;
	char *errmsg;
	char sqlstr[1024] = {0};

	if (name == NULL)
	{
		perror("Invalide name or passwd\n");
		return -1;
	}
	if (strlen(name) > 32)
	{
		perror("The entered name or password is too long\n");
		return -1;
	}
	sprintf(sqlstr, "UPDATE %s set keygen=%d where name='%s'",
			TABLE_USER, keygen, name);

#if __DEBUG
	printf("cmd: %s\n", sqlstr);
#endif

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		#if __PRINTF
		printf("Database updated successfully.\n");
		#endif
	}
	#if __PRINTF
	printf("\n");
	#endif
	return 1;
}

/* 用户上线、下线 */
/* 用户登陆成功后，或者发送下线申请，或者异常掉线，需要更新数据库的状态 */
/* 某个用户上线
UPDATE student SET fd=%d WHERE name='张立';
 某个用户下线
UPDATE student SET fd=-1 WHERE name='张立';*/
int db_user_on_off(int fd, char *name, unsigned int on_off)
{
	int value;
	char *errmsg;
	char sqlstr[1024] = {0};

	if (name == NULL)
	{
		perror("Invalid name or password entered ");
		return -1;
	}
	if (strlen(name) > 32)
	{
		perror("The entered name or password is too long ");
		return -1;
	}

	if (on_off == ONLINE)
	{
		value = fd;
	}
	else if (on_off == OFFLINE)
	{
		value = -1;
	}

	sprintf(sqlstr, "UPDATE  %s set fd=%d where name='%s'",
			TABLE_USER, value, name);

#if __DEBUG
	printf("cmd: %s\n", sqlstr);
#endif

	if (sqlite3_exec(db, sqlstr, NULL, NULL, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		#if __PRINTF
		printf("Database updated successfully.\n");
		#endif
	}
	#if __PRINTF
	printf("\n");
	#endif
	return 1;
}

/* 向所有在线用户发送信息 */
/* 得到某个用户的套接字描述符fd     
select fd from student where name = %s; */
int db_broadcast(int fd, char *buf)
{
	int peer_fd;
	int state = -1;
	int user_keygen; //接收信息的用户的keygen
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select fd,keygen from %s", TABLE_USER);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	index = ncolumn;
	
#if __DEBUG
	printf("ncolumn = %d, nrow = %d\n", ncolumn, nrow);
#endif

	for (i = 0; i < nrow; i++)
	{
		peer_fd = atoi(result[index]);
		index++;
		user_keygen = atoi(result[index]);
		index++;
		
#if __DEBUG
		printf("peer_fd = %d, user_keygen=%x\n", peer_fd, user_keygen);
#endif

		if (peer_fd != fd)
		{
			enc_send_srv(peer_fd, buf, strlen(buf), user_keygen);
			// write(temp_fd,buf,strlen(buf));
		}
	}
	sqlite3_free_table(result);
	return state;
}

/* 私聊 */
int db_private(int fd, char *dest, char *buf, int keygen)
{
	int peer_fd;
	int state = -1;
	int user_keygen; //接收信息的用户的keygen
	char **result, *errmsg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select fd,keygen from %s where name='%s'", TABLE_USER, dest);

#if __DEBUG
	printf("sqlstr: %s\n", sqlstr);
#endif

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	index = ncolumn;
	
#if __DEBUG
	printf("ncolumn = %d, nrow = %d\n", ncolumn, nrow);
#endif

	if (nrow > 0)
	{
		// find
		peer_fd = atoi(result[index]);
		index++;
		user_keygen = atoi(result[index]);
		index++;

#if __DEBUG
		printf("peer_fd = %d, user_keygen = %x\n", peer_fd, user_keygen);
#endif
		enc_send_srv(peer_fd, buf, strlen(buf), user_keygen);

		return 1;
	}
	else
	{
		// not find
		sprintf(buf, "The user %s does not exist.\n", dest);

		enc_send_srv(fd, buf, strlen(buf), keygen);
	}
	sqlite3_free_table(result);
	return state;
}

/* 查看在线用户 */
int db_list_online_user(int fd, int keygen)
{
	int state = -1;
	char **result, *errmsg;
	struct protocol msg;
	int nrow, ncolumn, i, j, index;
	char sqlstr[1024] = {0};

	sprintf(sqlstr, "select name from %s where fd>0",
			TABLE_USER);

	if (sqlite3_get_table(db, sqlstr, &result, &nrow, &ncolumn, &errmsg) != 0)
	{
		printf("An error occurred: %s\n", errmsg);
		sqlite3_free(errmsg);
		return -1;
	}
	index = ncolumn;
	
#if __DEBUG
	printf("ncolumn = %d, nrow = %d\n", ncolumn, nrow);
#endif

	for (i = 0; i < nrow; i++)
	{
		memset(&msg, 0, sizeof(msg));
		msg.cmd = ONLINEUSER;
		msg.state = ONLINEUSER_OK;
		strcpy(msg.name, result[index]);
		
		#if __PRINTF
		printf("The list online name is: %s, fd=%d\n", result[index], fd);
		#endif

		enc_send_srv(fd, &msg, sizeof(msg), keygen);
		index++;
		sleep(1);
	}
	memset(&msg, 0, sizeof(msg));
	msg.cmd = ONLINEUSER;
	msg.state = ONLINEUSER_OVER;

	enc_send_srv(fd, &msg, sizeof(msg), keygen);
	sqlite3_free_table(result);
	return 1;
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
		printf("Failed to open sqlite3: %s\n", sqlite3_errmsg(db));
		return -1;
	}

	/* Execute SQL statement */
	ret = sqlite3_exec(db, sql, NULL, 0, &errmsg);

	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	else
	{
		fprintf(stdout, "The database initialized successfully.\r\n");
	}
	return 0;
}

/* 关闭数据库 */
int database_close()
{
	sqlite3_close(db);
	exit(0);
}

/* 测试程序     */
#if 0
int main()
{
	int n;
	int ret = 0;
	char name[]="peng";
	char passwd[]="peng";

	database_init();


	//db_add_user(name,passwd);

	ret = db_user_if_reg(name);
	printf("db_user_if_reg = %d\n",ret);

	ret = db_user_pwd_corrct(name,passwd);
	printf("db_user_pwd_corrct = %d\n",ret);

	passwd[0]='3';
	ret = db_user_pwd_corrct(name,passwd);
	printf("db_user_pwd_corrct = %d\n",ret);

	db_user_on_off(3,name,ONLINE);

	
	database_close();

	return 0;
}
#endif
