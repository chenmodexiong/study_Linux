#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("下面将会创建子进程\n");

    pid_t id=fork();
    if(id<0)
    {
        perror("fork fail\n");
    }
    else if(id==0)
    {
        printf("I am child process\n");
        sleep(10);
    }
    else{ 
        printf("I am parent process\n");
        sleep(3);
        exit(0);
    }

    return 0;
}
