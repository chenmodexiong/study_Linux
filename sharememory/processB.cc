#include "comm.hpp"

int main()
{
    //申请共享内存
    int shmid = GetShm();
    // log(Debug, "create shm done");
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    // log(Debug, "attach shm done,shmaddr:0x%x", shmaddr);
    //打开管道文件
    int fd = open(FIFO_FILE, O_WRONLY);
    if (fd < 0)
    {
        log(Fatal, "error string: %s,error code:%d", strerror(errno), errno);
        exit(FIFO_OPEN_ERROR);
    }

    // 一旦挂接了共享内存，直接将它拿来就可以用，不需要缓冲区
    // ipc code
    while (true)
    {
        // char buffer[1024];
        std::cout << "Please Enter@";
        // memcpy(shmaddr,buffer,strlen(buffer)+1);
        fgets(shmaddr, 4096, stdin);
        write(fd,"c",1);
        
    }

    shmdt(shmaddr);
    // log(Debug, "detach shm done,shmaddr:0x%x", shmaddr);
    close(fd);
    return 0;
}