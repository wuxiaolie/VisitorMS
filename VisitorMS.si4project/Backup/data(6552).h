
/* 服务器数据库头文件 */

#ifndef _DB_DATA
#define _DB_DATA

#define OFFLINE -1
#define ONLINE 1

int db_add_user(char name[], char passwd[]);
int db_user_if_reg(char *name);
int db_user_pwd_corrct(char *name, char *passwd);
int db_user_on_off(int fd, char *name, unsigned int on_off);
int database_init();
int database_close();
int db_broadcast(int fd, char *buf);
int db_user_if_online(char *name, char *passwd);

#endif
