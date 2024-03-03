#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string>
void myhandler(int signo)
{
    std::cout<<"process get a signal: "<<signo<<std::endl;
}

void Usage(std::string proc)
{
    std::cout<<"Usage:\n\t"<<proc<<" signum pid\n\n";
} 
int main(int argc,char *argv[])
{
    //signal(SIGINT,myhandler);
    signal(SIGABRT,myhandler);
    int cnt=5;
    while(true)
    {
        std::cout<<"I am a process,pid:"<<getpid()<<std::endl;
        sleep(1);
        cnt--;
        //接口描述: int raise(int sig);
        //if(cnt==0) raise(SIGINT); 
        // raise作用:给自己发送信号,相当于:kill(getpid(),signum);
        
        //if(cnt==0) abort(); 
        //abort作用:给自己发送6号信号，但是不等于kill(getpid(),6);
        //现象：调用abort会被捕捉，但是依旧会返回来继续终止进程
        
    }

    // //mykill signum pid
    // if(argc!=3)
    // {
    //     Usage(argv[0]);
    //     exit(1);
    // }
    // int signum=std::stoi(argv[1]);
    // pid_t pid=std::stoi(argv[2]);
    // int n=kill(pid,signum);
    // if(n==-1)
    // {
    //     perror("kill\n");
    //     exit(2);
    // }

    return 0;
}

#ifdef __SIGNAL__TEST__
// typedef void (*sighandler_t)(int);
// sighandler_t signal(int signum, sighandler_t handler);
void myhandler(int signo)
{
    std::cout<<"process get a signal: "<<signo<<std::endl;
}
int main()
{
    //signal(SIGINT,myhandler);//设置一次之后都有效
    //signal(3,myhandler);
    //signal(19,myhandler);//不是所有的信号都能被捕捉,例如:9和19(在1~31中) （34~64的实时信号不考虑）
    //信号的产生与代码的运行是异步的 例如发送ls，即使l和s在显示器上是错乱的，但是依旧有效

    //验证哪些信号可以被捕捉
    for(int i=1;i<=31;i++)
    {
        signal(i,myhandler);
    }
    
    while (true)
    {
        std::cout << "I am a crazy process: %d " <<getpid()<< std::endl;
        sleep(1);
    }
    return 0;
}
#endif
