#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <thread>
using namespace std;
#define __TEST_CODE1__
//#define __TEST_CODE2__
//#define __TEST_CODE3__

// pthread 原生线程库
// c++11的线程库
#ifdef __TEST_CODE3__
void threadrun()
{
    while (true)
    {
        cout << "I am new thread for c++" << endl;
        sleep(1);
    }
}
int main()
{
    thread t1(threadrun);
    t1.join();
    return 0;
}
#endif

#ifdef __TEST_CODE1__
typedef class Request
{
public:
    Request(const int &start, const int &end, const std::string &threadName)
        : _start(start), _end(end), _threadName(threadName)
    {
    }

public:
    int _start;
    int _end;
    std::string _threadName;
} request;
typedef class Response
{
public:
    Response(const int &result, const int &exitcode)
        : _result(result), _exitcode(exitcode)
    {
    }

public:
    int _result;   // 计算结果
    int _exitcode; // 结果是否可靠
} reponse;
void *SumCount(void *args) // 线程的参数和返回值，可以传递一般参数，也可以传递对象
{
    request *rp = static_cast<request *>(args);
    reponse *rsp = new reponse(0, 0);
    for (int i = rp->_start; i <= rp->_end; i++)
    {
        cout << rp->_threadName << " is running,caling..." << i << endl;
        rsp->_result += i;
        usleep(10000);
    }
    delete rp;
    return rsp;
}
int main()
{
    pthread_t tid;
    request *rp = new request(1, 100, "Thread one");
    pthread_create(&tid, nullptr, SumCount, rp);
    void *ret;
    pthread_join(tid, &ret);
    reponse *rsp = static_cast<reponse *>(ret);
    cout << "rsp->_result:" << rsp->_result << " ,rsp->_exitcode:" << rsp->_exitcode << endl;
    delete rsp;
    return 0;
}
#endif

// #include <pthread.h>
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine)(void *), void *arg);
#ifdef __TEST_CODE2__
int g_val = 100;
// show被两个执行流调用，show函数重入
void show(const std::string &name)
{
    std::cout << name << "say# "
              << "hello thread" << std::endl;
}
void *threadRoutine(void *args)
{
    const char *name = (const char *)args;
    int cnt = 5;
    while (true)
    {
        printf("%s,pid:%d,g_val,&g_val:%p\n", name, getpid(), g_val, &g_val);
        // show("[new thread]");
        cnt--;
        sleep(1);
        if (cnt == 0)
            break;
    }
    // 线程终止不能用exit,会导致整个进程终止
    pthread_exit((void *)100);
    // return (void*)100;
}

int main()
{
    PTHREAD_CANCELED;
    pthread_t tid;
    pthread_create(&tid, nullptr, threadRoutine, (void *)"Thread 1"); // 不是系统调用
    sleep(2);
    pthread_cancel(tid);
    // while (true)
    // {
    //     std::cout << "main thread,pid:" << getpid() << " ";
    //     printf("create new thread tid:%p\n", tid);
    //     // show("[main thread]");
    //     sleep(1);
    // }
    void *retval;
    pthread_join(tid, &retval); // 阻塞等待新线程
    cout << "main thread quit...,retval:" << (long int)retval << endl;
    return 0;
}
#endif
