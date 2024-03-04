#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
void handler(int signo)
{
    cout << "catch a signo: " << signo << endl;
}
void Printpending(sigset_t &pending)
{
    for (int signo = 31; signo >= 1; signo--)
    {
        if (sigismember(&pending, signo))
        {
            cout << "1";
        }
        else
        {
            cout << "0";
        }
    }
    cout << endl
         << endl;
}

int main()
{
    signal(2, handler);
    // 1.先对2号信号进行屏蔽
    sigset_t bset, oset;
    sigemptyset(&bset);
    sigemptyset(&oset);
    sigaddset(&bset, 2);
    // 调用系统接口,将数据设置到block表
    sigprocmask(SIG_SETMASK, &bset, &oset);
    // 2.重复打印当前进程的pending
    sigset_t pending;
    int cnt = 0;
    while (true)
    {
        // 2.1 -- 获取pending
        int n = sigpending(&pending);
        if (n < 0)
            continue;
        // 2.2 -- 打印
        Printpending(pending);
        sleep(1);
        cnt++;
        if (cnt == 20)
        {
            printf("unblock 2 signo\n");
            sigprocmask(SIG_SETMASK, &oset, nullptr);
        }
    }
    // 3.发送2号信号

    return 0;
}
