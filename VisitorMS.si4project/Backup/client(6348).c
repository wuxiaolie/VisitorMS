
/* 聊天室客户端 */

#include <stdio.h>
#include <sqlite3.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "key.h"
#include "../../chat.h"

int sockfd;
int addrlen;
struct sockaddr_in server_addr;
static int glob_keygen;
pthread_t pid;

int login_f = -1;

/* 引入外部全局函数声明 */
extern void reset_keygen();
extern int born_sync();

/* 发送数据 */
int enc_send(int fd, void *data, int len)
{
	int ret;
	unsigned int keylen;
	int i, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	// printf("\n%s enter\n",__func__);

	/* 设置客户端的keygen */
	set_keygen(glob_keygen);
	/* 生成同步码sync */
	msg.sync = born_sync();

	key_num = len;
	/* 通过keygen、sync向密码机申请密钥 */
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);
	// print_array("\n明文:",(unsigned char *)data,keylen);

	/* 对明文数据加密 */
	for (i = 0; i < keylen; i++)
	{
		pdata[i] = ((unsigned char *)data)[i] ^ key[i];
	}
	// print_array("\n密文:",pdata,keylen);

	ret = write(fd, &msg, sizeof(msg));
	return ret;
}

/* 接收keygen */
/* 刚连接服务器时，接收keygen，此时应该设置set_keygen(glob_keygen) */
int enc_keygen_rcv(int fd, void *pmsg, int len)
{
	int i, ret;
	int rcvlen;
	int keylen, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	// printf("\n%s enter\n",__func__);
	rcvlen = read(fd, &msg, sizeof(msg));
	if (rcvlen <= 0)
	{
		return rcvlen;
	}
	
	printf("The rcvlen is %d\n", rcvlen);
	// printf("sync:%x\n",msg.sync);
	// print_array("密文:",pdata,(sizeof(struct protocol)));

	key_num = len;
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);

	/* 对明文数据解密 */
	for (i = 0; i < keylen; i++)
	{
		((unsigned char *)pmsg)[i] = pdata[i] ^ key[i];
	}
	// print_array("\n明文:",pmsg,keylen);

	return keylen;
}

/* 接收数据 */
int enc_rcv(int fd, void *pmsg, int len)
{
	int i, ret;
	int rcvlen;
	int keylen, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	// printf("\n%s enter\n",__func__);
	memset(&msg, 0, sizeof(msg));
	rcvlen = read(fd, &msg, sizeof(msg));
	// printf("rcvlen = %d\n",rcvlen);

	if (rcvlen <= 0)
	{
		return rcvlen;
	}
	// printf("sync:%x\n",msg.sync);

	// print_array("密文:",pdata,(sizeof(struct protocol)));

	/* 设置客户端的keygen */
	set_keygen(glob_keygen);
	key_num = rcvlen - 4; //去掉sync4字节
	/* 通过keygen、sync向密码机申请密钥 */
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);

	/* 根据密钥解密出明文 */
	for (i = 0; i < keylen; i++)
	{
		((unsigned char *)pmsg)[i] = pdata[i] ^ key[i];
	}
	// print_array("\n明文:",pmsg,keylen);

	return rcvlen;
}

/* 线程执行函数 */
void *func(void *arg)
{
	int len;
	char buf[512] = {0};
	struct protocol *pmsg;

	while (1)
	{
		if (login_f != 1)
		{
			sleep(1);
			continue;
		}

		memset(buf, 0, sizeof(buf));
		len = enc_rcv(sockfd, buf, sizeof(buf));

		if (len <= 0)
		{
			close(sockfd);
			return 0;
		}
		pmsg = (struct protocol *)buf;

		// 打印在线用户
		if ((pmsg->state == ONLINEUSER_OK) && (pmsg->cmd == ONLINEUSER))
		{
			printf("The name of the online user is: %s\t", pmsg->name);
			continue;
		}
		if ((pmsg->state == ONLINEUSER_OVER) && (pmsg->cmd == ONLINEUSER))
		{
			printf("\n");
			continue;
		}

		buf[len - 4] = '\0'; //接收的长度有4字节是sync
		// printf("len=%d\n",len);
		printf("#%s\n", buf);
		
	}
	return 0;
}

/* 公聊 */
static void broadcast_client(int fd)
{
	struct protocol msg;

	msg.cmd = BROADCAST;
	printf("Say:\n#");
	scanf("%s", msg.data);
	/* 由于scanf并没有把回车读入，所以需要额外读入一个回车，否则回车会被后面的getchar读入，导致打印信息被闪退 */
	getchar();

	int flag = 0;
	flag = enc_send(fd, &msg, sizeof(msg));

	if (flag > 0)
	{
		printf("The message sent successfully.\n");
	}
	else
	{
		printf("The message sent failed.\n");
	}
	getchar();
}

/* 私聊 */
static void private_client(int fd)
{
	struct protocol msg;

	msg.cmd = PRIVATE;

	printf("Please enter the name you want to chat with privately:\n#");
	scanf("%s", msg.name);

	printf("Say:\n#");
	scanf("%s", msg.data);
	/* 由于scanf并没有把回车读入，所以需要额外读入一个回车，否则回车会被后面的getchar读入，导致打印信息被闪退 */
	getchar();
	
	int flag = 0;
	flag = enc_send(fd, &msg, sizeof(msg));

	if (flag > 0)
	{
		printf("The message sent successfully.\n");
	}
	else
	{
		printf("The message sent failed.\n");
	}
	getchar();
	return;
}

/* 打印在线用户 */
void list_online_user(int sockfd)
{
	struct protocol msg;

	msg.cmd = ONLINEUSER;

	enc_send(sockfd, &msg, sizeof(msg));
	getchar();
	getchar();
	/*
	while(1)
	{
		read(sockfd ,&msg,sizeof(msg));
		if(msg.state == ONLINEUSER_OK)
		{
			printf("%s\t",msg.name);
		}else{
			break;
		}
	}*/
	return;
}

/* 注册 */
int registe(int fd)
{
	int ret;
	struct protocol msg, msgback;

	msg.cmd = REGISTE;
	printf("Please enter your name:\n");
	scanf("%s", msg.name);
	printf("Please enter your password:\n");
	scanf("%s", msg.data);

	ret = enc_send(fd, &msg, sizeof(msg));
	if (ret <= 0)
	{
		return ret;
	}

	ret = enc_rcv(fd, &msgback, sizeof(msgback));
	if (ret <= 0)
	{
		return ret;
	}
	// printf("msgback.state = %x\n",msgback.state);
	if (msgback.state != OP_OK)
	{
		printf("The name already exists, please try again.\n");
		getchar();
		getchar();
		return -1;
	}
	else
	{
		printf("Register successful!\n");
		getchar();
		getchar();
		return 0;
	}
}

/* 登录 */
int login(int fd)
{
	struct protocol msg, msgback;

	msg.cmd = LOGIN;
	printf("Please enter your name:\n");
	scanf("%s", msg.name);
	printf("Please enter your password:\n");
	scanf("%s", msg.data);

	enc_send(fd, &msg, sizeof(msg));
	enc_rcv(fd, &msgback, sizeof(msgback));
	if (msgback.state != OP_OK)
	{
		printf("User entered does not exist, please re-enter.\n");
		getchar();
		getchar();
		login_f = -1;
		return NAME_PWD_NMATCH;
	}
	else
	{
		printf("Login successful!\n");
		getchar();
		getchar();
		login_f = 1;
		return OP_OK;
	}
}

/* 退出登录 */
int logout(int fd)
{
	close(fd);
	login_f = -1;
}

/* 接收keygen密文，用默认的密钥解密keygen密文，然后将明文keygen设置到密码机，
函数运行结束后将进入菜单选项 */
int rcv_keygen(int sockfd)
{
	int len;
	struct protocol msgback;

	reset_keygen();
	len = enc_keygen_rcv(sockfd, &msgback, sizeof(msgback));
	if (len < 0)
	{
		return -1;
	}

	if (msgback.cmd != KEYGEN)
	{
		return -1;
	}
	glob_keygen = msgback.state;
	//printf("The keygen is: %x\n", glob_keygen);

	set_keygen(glob_keygen);
	return 1;
}

/* 主函数 */
int main(int argc, char **argv)
{
	int sel;
	int ret;
	int min_sel, max_sel;
	int portnumber;

	if (argc < 3)
	{
		printf("The portnumber is %s.\n", argv[0]);
		return -1;
	}
	
	if ((portnumber = atoi(argv[2])) < 0)
	{
		fprintf(stderr, "The portnumber %s is error.\n", argv[0]);
		exit(1);
	}
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("The socket initialization failed ");
		return -1;
	}

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	addrlen = sizeof(struct sockaddr_in);

	connect(sockfd, (struct sockaddr *)&server_addr, addrlen);
	pthread_create(&pid, NULL, func, NULL);

	//等待keygen
	ret = rcv_keygen(sockfd);
	if (ret < 0)
	{
		printf("Keygen not received, please reconnect to the server.\n");
		close(sockfd);
		return -1;
	}

	while (1)
	{
		// getchar();
		system("clear");
		if (login_f == -1)
		{
			printf("====================== Welcome to the chat room =====================\n");
			printf("---------------------------------------------------------------------\n");
			printf("---------Please enter a number to select the function to use---------\n");
			printf("                                                                     \n");
			printf("                  | 1. Request to register user                      \n");
			printf("                  | 2. Request login user                            \n");
			printf("																	 \n");
			printf("----------------Enter ctrl + c to turn off the connect---------------\n");
		}
		else if (login_f == 1)
		{
			printf("====================== Welcome to the chat room =====================\n");
			printf("---------------------------------------------------------------------\n");
			printf("---------Please enter a number to select the function to use---------\n");
			printf("                                                                     \n");
			printf("                  | 3. Enter public chat                             \n");
			printf("                  | 4. Enter private chat                            \n");
			printf("                  | 5. View list of online users                     \n");
			printf("																	 \n");
			printf("----------------Enter ctrl + c to turn off the connect---------------\n");
		}
		printf("--------------------Enter 0 to turn off the connect------------------\n");

		fflush(stdin);
		scanf("%d", &sel);
		if (sel == 0)
		{
			break;
		}
		if (login_f == 1)
		{
			min_sel = 3;
			max_sel = 5;
		}
		else if (login_f == -1)
		{
			min_sel = 1;
			max_sel = 2;
		}

		if (sel < min_sel || sel > max_sel)
		{
			printf("Sorry, the input is invalid, please re-enter.\n");
			continue;
		}
		switch (sel)
		{
		case 1:
			registe(sockfd);
			break;
		case 2:
			ret = login(sockfd);
			break;
		case 3:
			broadcast_client(sockfd);
			break;
		case 4:
			private_client(sockfd);
			break;
		case 5:
			list_online_user(sockfd);
			break;
		case 0:
			logout(sockfd);
			break;
		default:
			break;
		}
		if (sel == 0)
		{
			exit(0);
		}
	}
	return 0;
}
