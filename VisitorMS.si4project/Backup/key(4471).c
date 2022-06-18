
/* 服务端key加密功能源文件 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"
#include "../../chat.h"
//#include "../include/data.h"

static int keygen = 0;
static int offset = 0;
static int default_keygen = 0x9527;

/* 打印数组 */
void print_array(unsigned char title[], unsigned char data[], unsigned int len)
{
	int i;

	printf("%s ---- [%d]\n", title, len);
	for (i = 0; i < len; i++)
	{
		printf("%02x ", data[i]);
	}
	printf("\n");
}

/* 生成keygen */
int born_keygen()
{
	time_t t;

	srand(time(&t));

	return rand();
}

/* 生成sync同步码（密码机根据此同步码产生随机序列的密钥） */
int born_sync()
{
	time_t t;

	srand(time(&t));

	return rand();
}

/* 重新设置keygen，重置keygen，会影响生成的随机数序列 */
void reset_keygen()
{
	set_keygen(default_keygen);
}

/* 向密码机设置keygen，设置后会影响产生的随机密钥序列 */
void set_keygen(int key)
{
	keygen = key;
	offset = 0;
}

/* 产生随机数born_seed，根据同步码和keygen生成随机密钥种子 */
int born_seed(int sync, int key)
{
	return (sync ^ key);
}

/* 请求密钥，sync同步码，key_num申请的密钥个数，char key[]为申请的密钥存储缓存 */
/* 向密码机申请一定数量的用于加密数据的密钥，如果不设置新的keygen，
那么生成的密码会顺序产生下去，每次申请密钥都会记录上次生成的密钥的偏移，
下次在申请的时候，都会从上一位置继续分配密钥 */
int request_key(int sync, int key_num, char key[])
{
	int i, j, r;
	int seed;

	seed = born_seed(sync, keygen);

	srand(seed);
	if (key_num > MAX_KEY_REQUEST)
	{
		key_num = MAX_KEY_REQUEST;
	}

	for (i = 0; i < offset; i++)
	{
		rand();
	}

	for (j = 0; j < key_num; j++)
	{
		r = rand() & 0xff;
		key[j] = r;
	}
	offset += key_num;
	return key_num;
}
