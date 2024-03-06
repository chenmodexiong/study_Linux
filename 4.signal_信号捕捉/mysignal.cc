#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
using namespace std;

void handler(int signo)
{
    cout<<"I am process,pid:"<<getpid()<<" catch a signal,signo:"<<signo<<endl;
}
int main()
{
    //SIGCHLD(17)
    signal(SIGCHLD,handler);
    pid_t id=fork();
    if(id==0)
    {
        while(true)
        {
            cout<<"I am child process,pid:"<<getpid()<<" ppid:"<<getppid()<<endl;
            sleep(1);
            break;
        }
        exit(0);
    }
    while(true)
    {
        cout<<"I am father process,pid:"<<getpid()<<endl;
        sleep(1);
    }

    return 0;
}

#ifdef __TEST_CODE__
volatile int flag=0;//volatile防止编译器进行过度优化，保持内存可见性
void handler(int signo)
{
    cout<<"catch a signal:"<<signo<<endl;
    flag=1;
}
int main()
{
    signal(2,handler);
    while(!flag); //编译器可能对其进行一定程度的优化
    cout<<"process quit normal"<<endl;
    return 0;
}
#endif

#ifdef __TEST_CODE__
void PrintPending()
{
    sigset_t set;
    sigpending(&set);
    for (int signo = 1; signo <= 31; signo++)
    {
        if (sigismember(&set, signo))
            cout << "1";
        else
            cout << "0";
    }
    cout << "\n";
}
// 一、pending位图在执行信号捕捉之前先清0，再调用
// 二、信号被处理的时候，对应的信号会被加到block表中阻塞，防止信号被嵌套调用
void handler(int signo)
{
    cout << "catch a signal,number" << signo << endl;
    while (true)
    {
        PrintPending();
        sleep(1);
    }
}
int main()
{
    struct sigaction act, oact;
    memset(&act, 0, sizeof(act));
    memset(&oact, 0, sizeof(oact));
    act.sa_handler = handler; // SIG_DEF --默认  SIG_IGN --忽略
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,1);
    sigaddset(&act.sa_mask,3);
    sigaddset(&act.sa_mask,4);
    sigaction(2, &act, &oact);
    while (true)
    {
        cout << "I am a process,pid:" << getpid() << endl;
        sleep(1);
    }
    return 0;
}
#endif
