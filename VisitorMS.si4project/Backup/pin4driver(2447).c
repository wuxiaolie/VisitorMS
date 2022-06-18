#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd;
    int cmd = 0;

    printf("--------------------------------------\n");   
    fd = open("/dev/pin4", O_RDWR);
    if (fd < 0) {
        printf("Open /dev/pin4 failed!\n");
        perror("reason:");
    } else {
        printf("Open /dev/pin4 successfully!\n");
    }
    printf("Please input the command: 1/0\n");
    printf("0 - Equipment1 open  - set pin4 low\n");
    printf("1 - Equipment1 close - set pin4 high\n");
    scanf("%d", &cmd);
       
    if (cmd == 1) {   
        //printf("You entered : %d\n", cmd);
        fd = write(fd, &cmd, 1);
    } else if (cmd == 0) {
 		//printf("You entered : %d\n", cmd);
        fd = write(fd, &cmd, 1);
    } else {
        //printf("You entered : %dis error!\n", cmd);
    }
    close(fd);
}