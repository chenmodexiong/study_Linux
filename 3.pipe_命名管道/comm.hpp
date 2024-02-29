#pragma once
#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

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
