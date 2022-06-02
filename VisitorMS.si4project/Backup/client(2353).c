
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

int enc_send(int fd, void *data, int len)
{
	int ret;
	unsigned int keylen;
	int i, key_num;
	struct enc_data msg;
	unsigned char *pdata = (unsigned char *)&msg.data;
	unsigned char key[MAX_KEY_REQUEST] = {0};

	// printf("\n%s enter\n",__func__);

	set_keygen(glob_keygen);
	msg.sync = born_sync();

	key_num = len;
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);
	// print_array("\n明文:",(unsigned char *)data,keylen);

	for (i = 0; i < keylen; i++)
	{
		pdata[i] = ((unsigned char *)data)[i] ^ key[i];
	}
	// print_array("\n密文:",pdata,keylen);

	ret = write(fd, &msg, sizeof(msg));

	return ret;
}
//刚连接朝务器时，接收keygen，此时丝应该设置set_keygen(glob_keygen);
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
	printf("rcvlen = %d\n", rcvlen);
	// printf("sync:%x\n",msg.sync);
	// print_array("密文:",pdata,(sizeof(struct protocol)));

	key_num = len;
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);

	for (i = 0; i < keylen; i++)
	{
		((unsigned char *)pmsg)[i] = pdata[i] ^ key[i];
	}
	// print_array("\n明文:",pmsg,keylen);

	return keylen;
}
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

	set_keygen(glob_keygen);
	key_num = rcvlen - 4; //去掉sync4字节
	keylen = request_key(msg.sync, key_num, key);

	// print_array("密钥:",key,keylen);

	for (i = 0; i < keylen; i++)
	{
		((unsigned char *)pmsg)[i] = pdata[i] ^ key[i];
	}
	// print_array("\n明文:",pmsg,keylen);

	return rcvlen;
}

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
			return;
		}
		pmsg = (struct protocol *)buf;

		//  this is show online user,
		if ((pmsg->state == ONLINEUSER_OK) && (pmsg->cmd == ONLINEUSER))
		{
			printf("%s\t", pmsg->name);
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
}
void broadcast(int fd)
{
	struct protocol msg;

	msg.cmd = BROADCAST;
	printf("say:\n#");

	scanf("%s", msg.data);

	enc_send(fd, &msg, sizeof(msg));
}
void private(int fd)
{
	struct protocol msg;

	msg.cmd = PRIVATE;

	printf("input name you want to talk:\n#");
	scanf("%s", msg.name);

	printf("say:\n#");
	scanf("%s", msg.data);

	enc_send(fd, &msg, sizeof(msg));
}
void list_online_user(sockfd)
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
}
int registe(int fd)
{
	int ret;
	struct protocol msg, msgback;

	msg.cmd = REGISTE;
	printf("input your name\n");
	scanf("%s", msg.name);
	printf("input your passwd\n");
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
		printf("Name had exist,try again!\n");
		getchar();
		getchar();
		return -1;
	}
	else
	{
		printf("Regist success!\n");
		getchar();
		getchar();
		return 0;
	}
}
int login(int fd)
{
	struct protocol msg, msgback;

	msg.cmd = LOGIN;
	printf("input your name\n");
	scanf("%s", msg.name);
	printf("input your passwd\n");
	scanf("%s", msg.data);

	enc_send(fd, &msg, sizeof(msg));
	enc_rcv(fd, &msgback, sizeof(msgback));
	if (msgback.state != OP_OK)
	{
		printf("Name had exist,try again!\n");
		getchar();
		getchar();
		login_f = -1;
		return NAME_PWD_NMATCH;
	}
	else
	{
		printf("Login success!\n");
		getchar();
		getchar();
		login_f = 1;
		return OP_OK;
	}
}
int logout(int fd)
{
	close(fd);
	login_f = -1;
}

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
	printf("keygen:%x\n", glob_keygen);
	set_keygen(glob_keygen);

	return 1;
}

int main(int argc, char **argv)
{
	int sel;
	int ret;
	int min_sel, max_sel;
	int portnumber;

	if (argc < 3)
	{
		printf("cmd: %s ip portnumber\n", argv[0]);
		return;
	}
	// argv2 ��ŵ��Ƕ˿ں� ����ȡ�ö˿ڣ�ת�������ͱ���
	if ((portnumber = atoi(argv[2])) < 0)
	{
		fprintf(stderr, "Usage:%s hostname portnumber\a\n", argv[0]);
		exit(1);
	}
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket() fail\n");
		return;
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
		printf("没有收到keygen，请針新连接朝务器\n");
		close(sockfd);
		return -1;
	}

	while (1)
	{
		// getchar();
		system("clear");
		if (login_f == -1)
		{
			printf("\t 1 注册 \n");
			printf("\t 2 登录 \n");
		}
		else if (login_f == 1)
		{
			printf("\t 3 公蝊 \n");
			printf("\t 4 秝蝊 \n");
			printf("\t 5 在线列表 \n");
		}
		printf("\t 0 退出\n");

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
			printf("Valid choice ,try again\n");
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
			broadcast(sockfd);
			break;
		case 4:
		private
			(sockfd);
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
}
