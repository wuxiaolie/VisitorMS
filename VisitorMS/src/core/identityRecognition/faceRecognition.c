
#include "identityRecognition.h"

#include <curl/curl.h>
#include <unistd.h>

typedef unsigned int bool;
static char buf[10240] = {'\0'};

static size_t readData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    strncpy(buf, ptr, 10240);
}

static char *getPicBase64FromFile(char *filePath)
{
    char *bufPic;
    char cmd[128] = {'\0'};

    sprintf(cmd, "base64 %s > tmp_file", filePath);
    system(cmd);

    int fd = open("./tmp_file", O_RDWR);
    int filelen = lseek(fd, 0, SEEK_END); //计算文件大小
    lseek(fd, 0, SEEK_SET);               //移动光标重新回到开头
    bufPic = (char *)malloc(filelen + 2);
    memset(bufPic, '\0', filelen + 2); //清空
    read(fd, bufPic, filelen);
    close(fd);
    system("rm -f tmp_file");  //把临时生成的文件删掉

    return bufPic;
}

static bool postUrl(int numOfIdentity)
{
    CURL *curl;
    CURLcode res;

    char *key = "QEgxgMoZNAVjg4jyL1WGtY";
    char *secret = "fc7420fe2eed4f8b8406f0f19fdc4919";
    int typeId = 21;
    char *format = "xml";
    char *postString;

	printf("\r\n");
	printf("--------------------------------\r\n");
	//系统调用函数，查看照片库中照片是否存在
	if (access("./src/lib/libcurl/back_up_photo.jpg", F_OK) == -1) {
		printf("Sorry, you have not registered a face recognition account.\r\n");
		return FALSE;
	} else {
		printf("Successfully found your photo in face recognition database.\r\n");
	}
    char *bufPic1 = getPicBase64FromFile("./src/lib/libcurl/back_up_photo.jpg");
	//系统调用函数，查看用户上传的照片是否存在
	if (access("./src/lib/libcurl/back_up_photo.jpg", F_OK) == -1) {
		printf("Sorry, I can't find your photo in the specified directory.\r\n");
		return FALSE;
	} else {
		printf("Successfully found your photo in the specified directory.\r\n");
	}
    char *bufPic2 = getPicBase64FromFile("./src/tmp/photo.jpg");
	printf("--------------------------------\r\n");
	
    int len = strlen(key) + strlen(secret) + strlen(bufPic1) + strlen(bufPic2) + 124;
    postString = (char *)malloc(len);
    memset(postString, '\0', len);

	//拼接字符串
    sprintf(postString, "&img1=%s&img2=%s&key=%s&secret=%s&typeId=%d&format=%s",
            bufPic1, bufPic2, key, secret, 21, format);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");            // 指定cookie文件
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);                   // 指定post内容
        curl_easy_setopt(curl, CURLOPT_URL, "https://netocr.com/api/faceliu.do"); // 指定url
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, readData);                  //调用函数readData，将返回的数据发给readData
        res = curl_easy_perform(curl);

        //打印返回值
        if (strstr(buf, "是") != NULL) //查找字符串中是否含“是”
        {
            printf("Congratulations, face verification passed.\r\n");
			printf("--------------------------------\r\n");
            return TRUE;
        }
        else
        {
            printf("Sorry, you don't match the identification photos in the system.\r\n");
			printf("--------------------------------\r\n");
            return FALSE;
        }
        curl_easy_cleanup(curl);
    }

	return FALSE;
}

int faceRecognitionMain(int numOfIdentity)
{
    return postUrl(numOfIdentity);
}
















