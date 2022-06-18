
/* 服务端key加密功能头文件 */

#ifndef _KEY_STATION
#define _KEY_STATION
#define MAX_KEY_REQUEST 512

void set_keygen(int key);
int born_seed(int sync, int key);
int request_key(int sync, int key_num, char key[]);
int born_sync(void);

#endif
