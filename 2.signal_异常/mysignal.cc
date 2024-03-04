#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main()
{

    // signal(2,SIG_IGN);//忽略2号信号
    // signal(2,SIG_DFL);//默认递达方法
    // signal(2,handler);//自定义方法

    pid_t id = fork();
    if (id == 0)
    {
        // child
        int cnt = 500;
        while (cnt)
        {
            cout << "I am child process,pid:" << getpid() << " cnt=" << cnt << endl;
            sleep(1);
            cnt--;
        }
        exit(0);
    }
    // father
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        cout << "child quit info,rid:" << rid << " exit code: " << ((status >> 8) & 0XFF) << " exit signal: " << (status & 0X7F) << " core dump: "<< ((status>>7)&1) << endl;
    }
    return 0;
}

#ifdef __TEST_CODE__
void MyWork()
{
    std::cout << "do my work" << std::endl;
}
void handler(int signo)
{
    // MyWork();
    std::cout << "...get a signal,number" << signo << std::endl;
    // exit(1);
    int n = alarm(5);
    std::cout << "上个alarm剩余时间" << n << std::endl;
}

int main()
{
    signal(SIGALRM, handler);
    int n = alarm(50); // 闹钟 (14号信号) --- 不是异常，只是一种软件条件。
    while (true)
    {
        std::cout << "process is running...pid:" << getpid() << std::endl;
        sleep(1);
    }
    return 0;
}
#endif

#ifdef __TEST_CODE__
int main()
{
    signal(SIGSEGV, handler);
    // signal(SIGFPE,handler);
    sleep(3);
    std::cout << "before:" << std::endl;

    char buffer[1024];
    int n = 1024;
    n = read(4, buffer, 1024);
    printf("n=%d\n", n);
    perror("read");
    // int a=10;
    // int b=0;
    // int ret=a/b;//异常

    // int* point=nullptr;
    //*point=100;//异常--野指针

    // std::cout<<*point<<std::endl;

    std::cout << "after:" << std::endl;
    sleep(1);
    return 0;
}
#endif