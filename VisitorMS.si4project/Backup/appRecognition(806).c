
/* App验证源代码 */
/* 参考FTP server程序 */

#include "identityRecognition.h"

/* 定义用来存储信息块的结构体 */
struct Msg {
        char data[1024];
};

/* App验证 */
int AppRecognitionMain(int numOfIdentity)
{
	int s_fd;
	int c_fd;
	int n_read;

	struct sockaddr_in s_addr;  //定义服务器的套接字
	struct sockaddr_in c_addr;  //定义与执行connect的客户端建立连接的套接字
	struct Msg msg;  

	//初始化，将两个结构体的内容全部初始化为0
	memset(&s_addr, 0, sizeof(struct sockaddr_in));
	memset(&c_addr, 0, sizeof(struct sockaddr_in));

	/* 1.socket，申请socket描述符 */
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1) {
		perror("Ask for socket error\r\n");
		exit(-1);
	}
    
    /* 2.bind，将服务器IP地址和端口号与一个套接字进行绑定（将套接字与地址关联） */
	s_addr.sin_family = AF_INET;  //设置为TCP/IP协议族
	s_addr.sin_port = htons(atoi("8020"));  //设置端口号，由于传入的参数为字符串类型，要转换为int类型，htons为宏定义，用于避免出现大小端问题
	inet_aton("192.168.3.143", &s_addr.sin_addr);  //将IP地址在点分十进制和二进制表示形式之间进行转化

	bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));

	/* 3.listen，让服务器进入监听状态，等待客户端连接请求 */
	listen(s_fd, 5);  //s_fd等待连接队列最大为15

    int clen = sizeof(struct sockaddr_in);

	printf("Waiting for App connection ...\r\n");
	printf("--------------------------------------\r\n");

	//由于设定只允许手机连接一次，所以，这里不用while
    /* 4.accept，进入阻塞状态，获取客户端的连接请求，并建立连接 */
	c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen);
    //输出错误信息
	if(c_fd == -1)
		perror("Failed to establish connection\r\n");
    //打印客户端IP地址
    printf("App connection succeeded.\r\n");
	printf("The IP address of the App is:  %s\r\n",inet_ntoa(c_addr.sin_addr));
	printf("--------------------------------------\r\n");

	//清空msg结构体
	memset(msg.data, 0, sizeof(msg.data));
	//等待客户端输入，将所有数据都传到msg结构体中，返回值是读到的字节数
	n_read = read(c_fd, &msg, sizeof(msg));
   
	if(n_read == 0)	{
		printf("The App validation failed.\r\n");
		printf("--------------------------------------\r\n");
		return FALSE;
	}
	else if(n_read > 0)	{
		if (!strcmp("123312", msg.data)) {
			printf("The App verification login succeeded.\r\n");
			printf("--------------------------------------\r\n");
			return TRUE;
		}
	}				
    
    /* 关闭套接字，释放相应资源 */
	close(c_fd);  
	close(s_fd);
	return FALSE;

}

















