#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    printf("我是父进程,pid:%d,ppid:%d\n",getpid(),getppid());
    printf("下面将创建子进程使用exec系列函数用来验证程序替换\n");
    pid_t id=fork();    
    if(id<0) {
        perror("fork fail\n");
        exit(1);
    }
    else if(id == 0 ) {
        printf("我是子进程,pid:%d,ppid:%d\n",getpid(),getppid());
        //基础用法 
        //int execl(const char *path, const char *arg, ...);
       // int execlp(const char *file, const char *arg, ...);
       // int execle(const char *path, const char *arg, ...,char *const envp[]);
       // int execv(const char *path, char *const argv[]);
       // int execvp(const char *file, char *const argv[]);
        execl("/usr/bin/ls","ls","-a","-l",NULL);
        printf("看不见我,我被替换掉了\n"); 
        printf("看不见我,我被替换掉了\n"); 
        printf("看不见我,我被替换掉了\n");
    }
    else{
        int st; 
        pid_t ret=wait(&st);
        if(ret==id) {
            sleep(10);
            printf("子进程替换完成且正常退出,退出码:%d\n",WEXITSTATUS(st));
        }
        else {
            printf("子进程未能正常结束,退出码:%d",WEXITSTATUS(st));
        }
    }
    return 0;
}
