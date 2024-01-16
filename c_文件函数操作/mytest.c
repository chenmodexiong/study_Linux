#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd =open("bite",O_WRONLY|O_CREAT,0666); 
    if(fd<0)
    {
        perror("open fail\n");
        return 1;
    }
    int count=5;
    const char* msg="linus so easy!\n";
    int len=strlen(msg);
    while(count)
    {
        write(fd,msg,len);//写入
        count--;
    }
    close(fd);

    int fd2=open("bite",O_RDONLY);
    char buf[1024];
    while(1)
    {
        ssize_t sd=read(fd2,buf,len);//读到标准输出
        if(sd>0)
        {
            printf("%s",buf);
        }else {
            break;
        }
    }
    close(fd2);
    return 0;
}
