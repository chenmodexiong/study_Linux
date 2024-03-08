
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
#define __TEST_CODE__
// #include <pthread.h>
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine)(void *), void *arg);

#ifdef __TEST_CODE__
//show被两个执行流调用，show函数重入
void show(const std::string& name)
{
    std::cout<<name<<"say# "<<"hello thread"<<std::endl;
}
void *threadRoutine(void *args)
{
    while (true)
    {
        //std::cout << "new thread,pid: " << getpid() << std::endl;
        show("[new thread]");
        sleep(1);
    } 
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, threadRoutine, nullptr); //不是系统调用
    while (true)
    {
        //std::cout << "main thread,pid:" << getpid() << std::endl;
        show("[main thread]");

        sleep(1);
    }

    return 0;
}
#endif
