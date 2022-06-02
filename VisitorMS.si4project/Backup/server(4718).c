
/* 聊天室服务端 */

#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "data.h"
#include "../../chat.h"
#include "key.h"

#define __DEBUG 0    // 为0则不打印调试信息，为1则打印调试信息
#define __PRINTF 0   // 为0则不打印调试信息，为1则打印调试信息

/* 引入外部全局函数声明 */
extern int db_add_user(char name[], char passwd[]);
extern int db_user_if_reg(char *name);
extern int db_user_pwd_corrct(char *name, char *passwd);
extern int db_user_on_off(int fd, char *name, unsigned int on_off);
extern int database_init();
extern int database_close();
extern int db_private(int fd, char *dest, char *buf, int keygen);
extern int db_update_keygen(char *name, int keygen);
extern void reset_keygen();
extern int born_keygen();
extern int db_list_online_user(int fd, int keygen);

/* 引入外部全局变量声明         - 数据库互斥锁 */
extern pthread_mutex_t db_mutex;

/* 发送数据 */
/* 不同的客户端，keygen是不同的，调用该函数之前需要从数据库中获取对应的客户端的keygen */
int enc_send_srv(int fd, void *data, int len, int keygen)
{
	int ret;
	unsigned int keylen;
	int i, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	#ifdef PRINTF
	printf("\n%s enter\n", __func__);
	#endif

	/* 生成同步码sync */
	msg.sync = born_sync();   
	key_num = len;

	// printf("sync:%x\n",msg.sync);

	/* 上锁！多客户端会有一定概率调度TBD(数据库)	*/
	/* 申请锁 */
	pthread_mutex_lock(&db_mutex);
	/* 设置客户端的keygen */
	set_keygen(keygen);
	/* 通过keygen,sync向密码机申请密钥 */
	keylen = request_key(msg.sync, key_num, key);
	/* 释放锁 */
	pthread_mutex_unlock(&db_mutex);
	// print_array("密钥:",key,keylen);

	/* 对明文数据加密 */
	for (i = 0; i < keylen; i++)
	{
		pdata[i] = ((unsigned char *)data)[i] ^ key[i];
	}
	// print_array("\n密文:",(unsigned char *)&msg.data,keylen);

	/* 发送密文数据 */
	ret = write(fd, &msg, len + 4);

	return ret;
}

/* 接收数据 */
int enc_rcv_srv(int fd, void *pmsg, int len, int keygen)
{
	int i, ret;
	int rcvlen;
	int keylen, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	#ifdef PRINTF
	printf("\n%s enter\n", __func__);
	#endif

	rcvlen = read(fd, &msg, sizeof(msg));
	if (rcvlen <= 0)
	{
		return rcvlen;
	}

	/* 上锁！多客户端会有一定概率调度TBD	*/
	/* 申请锁 */
	pthread_mutex_lock(&db_mutex);
	/* 设置客户端的keygen */
	set_keygen(keygen);
	key_num = len;
	/* 通过keygen,sync向密码机申请密钥 */
	keylen = request_key(msg.sync, key_num, key);
	/* 释放锁 */
	pthread_mutex_unlock(&db_mutex);

	// print_array("密钥:",key,keylen);

	/* 根据密钥解密出明文 */
	for (i = 0; i < keylen; i++)
	{
		((unsigned char *)pmsg)[i] = pdata[i] ^ key[i];
	}
	// print_array("\n明文:",pmsg,keylen);

	return keylen;
}

/* 公聊 */
void broadcast(int fd, char *name, struct protocol *msg, int keygen)
{
	int i;
	char buf[128] = {0};

	sprintf(buf, "%s say:%s\n", name, msg->data);

	db_broadcast(fd, buf);
}

/* 私聊 */
void private(int fd, char *name, struct protocol *msg, int keygen)
{
	int dest_index;
	char buf[128] = {0};

	#ifdef PRINTF
	printf("\n%s enter\n", __func__);
	#endif

	sprintf(buf, "%s say:%s\n", name, msg->data);

	#ifdef PRINTF
	printf("\n%s() to %s : buf:%s\n", __func__, msg->name, buf);
	#endif

	db_private(fd, msg->name, buf, keygen);
}

/* 用户注册 */
void regist(int sockfd, int *index, struct protocol *msg, int keygen)
{
	int dest_index;
	char buf[128] = {0};
	struct protocol msg_back;

	msg_back.cmd = REGISTE;

	//查询用户是否注册
	dest_index = db_user_if_reg(msg->name);

	if (dest_index == -1)
	{ 
		// 此用户可以注册
		*index = db_add_user(msg->name, msg->data);
		msg_back.state = OP_OK;
		
		#ifdef PRINTF
		printf("user %s regist success!\n", msg->name);
		#endif
	}
	else
	{
		msg_back.state = NAME_EXIST;
		
		#ifdef PRINTF
		printf("user %s exist!\n", msg->name);
		#endif
	}
	enc_send_srv(sockfd, &msg_back, sizeof(msg_back), keygen);
	return;
}

/* 用户登录 */
void login(int sockfd, int *index, struct protocol *msg, int keygen)
{
	int i;
	int ret;
	int dest_index;
	char buf[128] = {0};
	struct protocol msg_back;

	msg_back.cmd = LOGIN;

	//查询用户是否注册
	dest_index = db_user_if_reg(msg->name);
	if (dest_index == -1)
	{
		msg_back.state = USER_NOT_REGIST;
		strcpy(buf, "there is no this user\n");
		
		#ifdef PRINTF
		printf("user %s login fail!\n", msg->name);
		#endif

		enc_send_srv(sockfd, &msg_back, sizeof(msg_back), keygen);
		return;
	}

	// check name && passwd
	ret = db_user_if_online(msg->name, msg->data);

	#ifdef PRINTF
	printf("login() ret=%d\n", ret);
	#endif
	
	if (ret == -2)
	{
		msg_back.state = USER_NOT_REGIST;
		strcpy(buf, "user login not exist\n");

		#ifdef PRINTF
		printf("user %s login fail!\n", msg->name);
		#endif

		enc_send_srv(sockfd, &msg_back, sizeof(msg_back), keygen);
		return;
	}
	else if (ret == -1)
	{
		//保存keygen TBD
		db_update_keygen(msg->name, keygen);

		//可以登录
		db_user_on_off(sockfd, msg->name, ONLINE);

		msg_back.state = OP_OK;
		strcpy(msg_back.data, "login success\n");

		#ifdef PRINTF
		printf("user %s login success!index =%d \n", msg->name, *index);
		#endif
		
		enc_send_srv(sockfd, &msg_back, sizeof(msg_back), keygen);
	}
	else
	{
		msg_back.state = USER_LOGED;
		strcpy(buf, "user had login already\n");

		#ifdef PRINTF
		printf("user %s login fail!\n", msg->name);
		#endif

		enc_send_srv(sockfd, &msg_back, sizeof(msg_back), keygen);
		return;
	}

	//通知所有客户端，某个用户上线了
	sprintf(buf, "%s online\n", msg->name);

	db_broadcast(sockfd, buf);
	return;
}

/* 随机生成密钥keygen，并保存到数据库user.db，用默认密钥向密码机申请密钥，
对keygen进行加密，最后发送keygen密文给客户端，函数运行结束后将进入协议处理单元 */
/* 客户端连接服务器后，服务器首先发送keygen给客户端用户产生密钥序列 */
int keygen_send(int fd, int *keygen)
{
	int ret;
	unsigned int keylen;
	int i, key_num;
	struct enc_data msg;
	struct protocol *pmsg = (struct protocol *)&msg.data;
	unsigned char *pdata = (unsigned char *)pmsg;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	pmsg->cmd = KEYGEN;
	key_num = sizeof(struct protocol);
	msg.sync = born_sync();

	/* 上锁！多客户端会有一定概率调度TBD(数据库)	*/
	/* 申请锁 */
	pthread_mutex_lock(&db_mutex);
	/* 设置客户端的keygen */
	reset_keygen();
	/* 通过keygen,sync向密码机申请密钥 */
	keylen = request_key(msg.sync, key_num, key);
	/* 释放锁 */
	pthread_mutex_unlock(&db_mutex);

	//	printf("sync:%x\n",msg.sync);
	//	print_array("密钥:",key,keylen);

	//生成keygen
	*keygen = born_keygen();
	pmsg->state = *keygen;

	//	printf("keygen:%x\n",pmsg->state);
	//	print_array("\n明文:",pdata,keylen);

	for (i = 0; i < keylen; i++)
	{
		pdata[i] = pdata[i] ^ key[i];
	}
	//	print_array("\n密文:",pdata,keylen);

	ret = write(fd, &msg, sizeof(msg));

	return ret;
}

/* 线程执行函数 */
void *func(void *arg)
{
	int sockfd = *((int *)arg);
	char buf[256];
	int len;
	int index = -1; //该用户在在线用户列表的下标
	struct protocol msg;
	char name[32] = {0};
	int keygen;

	free(arg);

	//先发送keygen
	keygen_send(sockfd, &keygen);

	//进入聊天了
	while (1)
	{
		memset(&msg, 0, sizeof(msg));
		len = enc_rcv_srv(sockfd, &msg, sizeof(msg), keygen);
		if (len <= 0)
		{ 
			//下线
			memset(buf, 0, sizeof(buf));
			if (strlen(name) > 0)
			{
				sprintf(buf, "%s offline\n", name);
				
				#ifdef PRINTF
				printf("%s", buf);
				#endif
				
				db_broadcast(sockfd, buf);

				//从在线列表中删除
				db_user_on_off(sockfd, name, OFFLINE);
			}
			close(sockfd);
			return 0;
		}

		//注册登录 显示在线用户，keygen不用查询
		//公聊私聊的keygen 需要从数据中得到
		//登录成功，需要保存keygen
		switch (msg.cmd)
		{
		case REGISTE:
			regist(sockfd, &index, &msg, keygen);
			break;
		case LOGIN:
			login(sockfd, &index, &msg, keygen);
			strcpy(name, msg.name);
			break;
		case BROADCAST:
			broadcast(sockfd, name, &msg, keygen);
			break;
		case PRIVATE:
		private
			(sockfd, name, &msg, keygen);
			break;
		case ONLINEUSER:
			db_list_online_user(sockfd, keygen);
			break;
		default:
			break;
		}
	}
}

/* 主函数 */
int main(int argc, char **argv)
{
	int lsfd, newfd;
	int addrLen, cliaddrlen;
	struct sockaddr_in my_addr;
	struct sockaddr_in cli_adr;
	pthread_t pid;
	int *arg;
	int i;
	int portnumber;

	if (argc < 2)
	{
		printf("The portnumber is %s.\r\n", argv[0]);
		return -1;
	}

	if (database_init() < 0)
	{
		printf("Database open failed.\r\n");
		return -1;
	}

	if ((portnumber = atoi(argv[1])) < 0)
	{
		fprintf(stderr, "The portnumber %s is error.\r\n", argv[0]);
		exit(1);
	}

	lsfd = socket(PF_INET, SOCK_STREAM, 0);
	
	if (lsfd < 0)
	{
		perror("The socket initialization failed.\r\n");
		return 0;
	}
	
	bzero(&my_addr, sizeof(struct sockaddr_in));
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(portnumber);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addrLen = sizeof(struct sockaddr_in);

	if (bind(lsfd, (struct sockaddr *)&my_addr, addrLen) < 0)
	{
		perror("The bind initialization failed.\r\n");
		return -1;
	}

	listen(lsfd, 5);
	cliaddrlen = sizeof(struct sockaddr_in);

	while (1)
	{
		newfd = accept(lsfd, (struct sockaddr *)&cli_adr, &cliaddrlen);

		#ifdef PRINTF
		printf("The client connection succeeded! IP: %s  PORT: %d\n",
			   inet_ntoa(cli_adr.sin_addr), cli_adr.sin_port);
		#endif

		arg = malloc(sizeof(int));
		*arg = newfd; 			//必须搞清楚为什么要申请内存

		pthread_create(&pid, NULL, func, (void *)arg);
	}
	close(newfd);
	close(lsfd);
	
	return 0;
}
