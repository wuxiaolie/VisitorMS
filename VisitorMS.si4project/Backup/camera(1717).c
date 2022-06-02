
#include "camera.h"

/* 打开摄像头 */
void openCamera(void)
{
	char msg[1024];
	/* 创建一个文件描述符 */
	int fd = open("/tmp/camera_tmp_file.c", O_RDWR | O_CREAT);
		
	/* 调用fork()生成子进程，在子进程中调用/bin/sh -c来执行参数的指令，
	是以创建管道的方式创建子进程并连接到子进程的标准输出设备或标准输入设备，
	功能是执行指令将输出放入文件中，返回文件指针 */
	FILE *r1 = popen("/home/pi/raspberry/mjpg-streamer/mjpg-streamer-experimental/start.sh", "r");
	/* 从文件读取1个数据项，每个数据项大小为sizeof(msg),将读取到的数据存放在参数ptr指向的缓冲区中 */
	fread(msg, sizeof(msg), 1, r1);
	/* 将数据写入套接字描述符中 */
	lseek(fd, 0, SEEK_SET);
	write(fd, &msg, sizeof(msg));

	/* 打印提示信息 */
	move(0, 0);
	printw("============ Welcome to Haoqing visitor management system ===========\n");
	printw("---------------------------------------------------------------------\n");
	printw("\n");
	printw("\n");
	printw("-------------------------Camera open seccess!------------------------\n");
	printw("----------------------Open web page to view video--------------------\n");
	printw("----------------http://192.168.3.143:8080/index.html-----------------\n");
	printw("-----------------------Enter any key to return-----------------------\n");
	printw("                                                                     \n");
	printw("                                                                     \n");
	printw("---------------------------------------------------------------------\n");
	refresh(); 
	getchar();

	
	close(fd);
}

/* 关闭摄像头 */
void closeCamera(void)
{

}




