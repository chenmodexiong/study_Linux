#include "comm.hpp"
#include "log.hpp"
// 管理管道文件
int main()
{
    Log log;
    log.Enable(Onefile);
    // log.Enable(Classfile);
    Init init;
    // 打开管道
    int fd = open(FIFO_FILE, O_RDONLY); // 阻塞，等待客户端写入文件
    if (fd < 0)
    {
        log(Fatal, "error string: %s,error code: %d", strerror(errno), errno);
        exit(FIFO_OPEN_ERROR);
    }
    // log.LogMessage(Info,"server open file done,error string: %s,error code: %d",strerror(errno),errno);
    // log.LogMessage(Warning,"server open file done,error string: %s,error code: %d",strerror(errno),errno);
    // log.LogMessage(Debug,"server open file done,error string: %s,error code: %d",strerror(errno),errno);
    // log.LogMessage(Fatal,"server open file done,error string: %s,error code: %d",strerror(errno),errno);
    log(Info, "server open file done,error string: %s,error code: %d", strerror(errno), errno);
    log(Warning, "server open file done,error string: %s,error code: %d", strerror(errno), errno);
    log(Debug, "server open file done,error string: %s,error code: %d", strerror(errno), errno);
    log(Fatal, "server open file done,error string: %s,error code: %d", strerror(errno), errno);
    // 开始通信
    while (true)
    {
        char buffer[1024] = {0};
        int x = read(fd, buffer, sizeof(buffer));
        if (x > 0)
        {
            buffer[x] = 0;
            std::cout << "client say# " << buffer << std::endl;
        }
        else if (x == 0)
        {
            log(Debug, "client quit,me too,error string: %s,error code: %d", strerror(errno), errno);
            break;
        }
        else
            break;
    }
    // 关闭信道
    close(fd);

    return 0;
}