#ifndef __COMM_HPP__
#define __COM_HPP__
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "log.hpp"
#define EXITCODE 1
Log log;
const std::string pathname = "/home/lzb";
const int proj_id = 0x6666;
// 共享内存的大小建议一定是4096的整数倍，以4kb为单位
// 假设申请4097则实际申请的是4096*2，能使用的只有4097
const int size = 4096;
key_t GetKey()
{
    key_t k = ftok(pathname.c_str(), proj_id);
    if (k < 0)
    {
        log(Fatal, "ftok error:%s", strerror(errno));
        exit(EXITCODE);
    }
    log(Info, "ftok success,key is :0x%x", k);
    return k;
}
int GetShareMemHelper(int flag)
{
    key_t key = GetKey();
    int shmid = shmget(key, size, flag);
    if (shmid < 0)
    {
        log(Fatal, "create share memory error:%s", strerror(errno));
        exit(EXITCODE);
    }
    log(Info, "create share memory success,shmid:%d", shmid);
    return shmid;
}
int CreateShm()
{
    return GetShareMemHelper(IPC_CREAT | IPC_EXCL | 0666);
}
int GetShm()
{
    return GetShareMemHelper(IPC_CREAT);
}

#define FIFO_FILE "./myfifo"
#define MODE 0664

enum
{
    FIFO_CREATE_ERROR = 1,
    FIFO_DELETE_ERROR,
    FIFO_OPEN_ERROR
};

class Init
{
public:
    Init()
    {
        // 创建管道
        int n = mkfifo(FIFO_FILE, MODE);
        if (n == -1)
        {
            perror("mkfifo");
            exit(FIFO_CREATE_ERROR);
        }
    }
    ~Init()
    {
        int m = unlink(FIFO_FILE);
        if (m == -1)
        {
            perror("unlink");
            exit(FIFO_DELETE_ERROR);
        }
    }
};

#endif
