#include "comm.hpp"
#include "log.hpp"
// 管理管道文件
int main()
{
    // std::cout << sum(2, 1, 3) << std::endl;
    // std::cout << sum(3, 1, 2, 3) << std::endl;
    // std::cout << sum(4, 1, 2, 3, 4) << std::endl;
    // std::cout << sum(5, 6, 7, 8, 9, 10) << std::endl;

    Init init;

    // 打开管道
    int fd = open(FIFO_FILE, O_RDONLY);//阻塞，等待客户端写入文件
    if (fd < 0)
    {
        perror("open");
        exit(FIFO_OPEN_ERROR);
    }
    std::cout<<"server open file done"<<std::endl;
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
            std::cout << "client quit,me too!" << std::endl;
            break;
        }
        else
            break;
    }
    // 关闭信道
    close(fd);

    return 0;
}