#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
#define N 2
#define NUM 1024
//Child
void Writer(int wfd)
{
    string str = "hello,I am child";
    pid_t self = getpid();
    int number = 0;
    char buffer[NUM];
    while (true)
    {
        //构建字符串
        // buffer[0] = 0; // 字符串清空，提醒表示把这个数组当做字符串了
        // snprintf(buffer, sizeof(buffer), "%s-%d-%d", str.c_str(), self, number++);
        //cout << buffer << endl;
        //写入给father
        // write(wfd,buffer,strlen(buffer));
        char c='c';
        write(wfd,&c,1);
        cout<<number++<<endl;
        sleep(0);
    }
}
//Father
void Reader(int rfd)
{
    char buffer[NUM];
    while(true)
    {
        buffer[0]=0;
        ssize_t n=read(rfd,buffer,sizeof(buffer)); //sizeof != strlen 用sizeof表示缓冲区的总大小
        if(n>0)
        {
            buffer[n]=0; //0 =='\0'
            cout<<"father get a message["<<getpid()<<"]#"<<buffer<<endl;
            sleep(50);
        }
    }
}
int main()
{
    int pipefd[N] = {0};
    int val = pipe(pipefd);
    if (val < 0)
        return 1;
    cout << "pipefd[0]=" << pipefd[0] << ", pipefd[1]=" << pipefd[1] << endl;
    pid_t id = fork();
    if (id < 0)
        return 2;
    if (id == 0)
    {
        // child
        close(pipefd[0]);
        // IPC code
        Writer(pipefd[1]);
        exit(0);
    }
    // father
    close(pipefd[1]);
    // IPC code
    Reader(pipefd[0]);
    pid_t rid = waitpid(id,nullptr,0);
    if(rid<0) return 3;
    return 0;
}
