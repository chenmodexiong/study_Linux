#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd=open("bite",O_CREAT|O_WRONLY|O_APPEND,0666);
    if(fd<0)
    {
        perror("open fail\n");
        return -1;
    }
    int count=5;
    const char* str="I like linux!\n";
    while(count--)
    {
        write(fd,str,strlen(str));
    }
    close(fd);
    return 0;
}
