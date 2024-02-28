#include "Task.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unistd.h>
#include <ctime>
#include <sys/stat.h>
#include <sys/wait.h>
const int processnum = 10;
std::vector<task_t> tasks;
// 先描述
class channel
{
public:
    channel(int cmdfd, int slaverid, const std::string &processname)
        : _cmdfd(cmdfd), _slaverid(slaverid), _processname(processname)
    {
    }
public:
    int _cmdfd;               // 发送任务的文件描述符
    pid_t _slaverid;          // 子进程的pid
    std::string _processname; // 子进程的名字，方便打印日志
};

void slaver()
{
    while (true)
    {
        int cmdcode = 0;
        int n = read(0, &cmdcode, sizeof(int)); // 子进程读取任务码，无任务码则阻塞，管道是面向字节流的，按4byte读取
        if (n == sizeof(int))
        {
            // 执行cmdcode对应的任务列表
            std::cout << "slaver say@ get a command: " << getpid() << ": cmdcode: " << cmdcode << std::endl;
            if (cmdcode >= 0 && cmdcode < tasks.size())
            {
                tasks[cmdcode]();
            }
        }
        if(n==0) break;
    }
}

void InitProcessPool(std::vector<channel> *channels)
{

    for (int i = 0; i < processnum; i++)
    {
        int pipefd[2]; // 临时空间
        int n = pipe(pipefd);
        assert(!n); // asseert只在debug下有效,正常情况下要写成判断
        (void)n;

        pid_t id = fork();
        if (id == 0) // child
        {
            close(pipefd[1]);
            dup2(pipefd[0], 0); // 子进程的标准输入重定向到管道的读端
            slaver();           // 子进程的work
            std::cout<<"process:"<<getpid()<<" quit"<<std::endl;
            exit(0);
        }
        // father
        close(pipefd[0]);

        // 添加channel字段
        std::string name = "process-" + std::to_string(i);
        channels->push_back(channel(pipefd[1], id, name));
    }
}
void Debug(const std::vector<channel> &channels)
{
    for (const auto &c : channels)
    {
        std::cout << c._cmdfd << " " << c._slaverid << " " << c._processname << std::endl;
    }
}
void Menu()
{
    std::cout<<"#########################################################"<<std::endl;
    std::cout<<"########    1.刷新日志      2.刷新野怪          ###########"<<std::endl;
    std::cout<<"########    3.检测软件更新  4.更新血条和蓝量    ###########"<<std::endl;
    std::cout<<"########         -1.退出                       ###########"<<std::endl;
    std::cout<<"#########################################################"<<std::endl;
}
void ctrlSlaver(std::vector<channel> &channels)
{
    int which=0; 
    while(true)
    {
        Menu();
        std::cout<<"Please Enter@";
        int select=0;
        std::cin>>select;
        if(select<=0 || select>=5) break;

        // 1.选择任务
        int cmdcode=select-1;
        //int cmdcode = rand() % tasks.size();
        // 2.选择进程 -- 两种方式：随机和轮循
        // int processpos = rand() % channels.size();
        // std::cout << "father say cmdcode: " << cmdcode << " already send to " << channels[processpos]._slaverid << " process name: " << channels[processpos]._processname << std::endl;
        std::cout << "father say cmdcode: " << cmdcode << " already send to " << channels[which]._slaverid << " process name: " << channels[which]._processname << std::endl;
        // 3.发送任务
        //write(channels[processpos]._cmdfd, &cmdcode, sizeof(cmdcode));
        write(channels[which]._cmdfd, &cmdcode, sizeof(cmdcode));
        which++;
        which%=channels.size();
        sleep(1);
    }
}
void QuitProcess(const std::vector<channel> &channels)
{
    for(const auto &c:channels)
    {
        close(c._cmdfd);
    }
    sleep(5);
    for(const auto &c:channels)
    {
        waitpid(c._slaverid,nullptr,0);
    }
    sleep(5);
}
int main()
{
    LoadTask(&tasks);
    srand((unsigned int)time(nullptr) ^ getpid() ^ 1023); // 随机数种子,位操作让随机性更大
    // 再组织
    std::vector<channel> channels;
    // 1.初始化
    InitProcessPool(&channels);
    // test
    // Debug(channels);

    // 2.控制子进程
    ctrlSlaver(channels);

    // 3.清理收尾
    QuitProcess(channels);

    return 0;
}