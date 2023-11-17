#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    // printf("test\n");
    printf("I am parent, pid:%d,ppid:%d\n",getpid(),getppid());
    pid_t pid=fork(); 
    if(pid<0) {
        perror("error");
        exit(0);
        //_exit(0);
        //return
        //三种返回方式
    }
    else if(pid==0) {
        //execlp("./a.out",NULL);
        printf("I am child, pid:%d,ppid:%d\n",getpid(),getppid());
        execl("/usr/bin/ls","ls","-l","-a",NULL);
        //下面打印不会执行，因为execl进程已经替换
        printf("I am child, pid:%d,ppid:%d\n",getpid(),getppid());
    }
    else {
        pid_t ret=waitpid(pid,NULL,0);//等子进程正常结束,返回子进程pid
        if(ret>0)
             printf("I am parent, pid:%d,ppid:%d\n",getpid(),getppid());
    }

    return 0;
}
