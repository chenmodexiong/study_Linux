#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("I am parent,pid:%d,ppid:%d\n",getpid(),getppid());
    pid_t id=fork();
    if(id<0) {
       perror("fork fail\n");
       exit(1);
    }
    else if(id == 0) {
        //子进程
       sleep(20); 
       exit(10);
    }
    else {
       int status; 
       int ret=wait(&status);
       if(ret>0 && (status & 0x7F)==0) {
           //正常退出
            printf("child exit code:%d\n",(status>>8)&0x7F);
       } else if(ret>0)
       {
           //异常退出
           printf("sig code:%d\n",status&0x7F);
       }
    }
    return 0;
}
