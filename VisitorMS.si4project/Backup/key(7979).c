
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

/*  */
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

/*  */
int born_keygen()
{
	time_t t;

	srand(time(&t));

	return rand();
}

/*  */
int born_sync()
{
	time_t t;

	srand(time(&t));

	return rand();
}

/*  */
void reset_keygen()
{
	set_keygen(default_keygen);
}

/*  */
void set_keygen(int key)
{
	keygen = key;
	offset = 0;
}

/*  */
int born_seed(int sync, int key)
{
	return (sync ^ key);
}

/*  */
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
