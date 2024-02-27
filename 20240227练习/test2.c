#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	int fd = open("log.txt", O_WRONLY | O_CREAT);
	if (fd < 0)
	{
		//打开失败
		perror("open");//输出对应的错误码
		return 1;
	}
	printf("fd: %d\n", fd);
}
