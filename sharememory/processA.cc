#include "comm.hpp"

extern Log log;
int main()
{
    Init init;
    int shmid = CreateShm();
    // log(Debug,"create shm done");
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    // log(Debug,"attach shm done,shmaddr:0x%x",shmaddr);

    // 打开管道文件 -- 通过管道实现共享内存间的同步与互斥
    int fd = open(FIFO_FILE, O_RDONLY); // 等待写入方打开后，才会打开管道，向后执行 open阻塞等待
    if (fd < 0)
    {
        log(Fatal, "error string: %s,error code:%d", strerror(errno), errno);
        exit(FIFO_OPEN_ERROR);
    }

    struct shmid_ds shmds;
    // 一旦挂接了共享内存，有人写入数据则立马就可以看到，不需要经过系统调用
    // ipc code
    while (true)
    {
        char c;
        ssize_t s = read(fd, &c, 1);
        if (s == 0)
            break;
        else if (s < 0)
            break;

        std::cout << "client say@" << shmaddr << std::endl; // 直接访问共享内存
        sleep(1);

        shmctl(shmid, IPC_STAT, &shmds);
        std::cout << "shm size: " << shmds.shm_segsz << std::endl;
        std::cout << "shm natth: " << shmds.shm_nattch << std::endl;
        // std::cout << "shm __key: " << shmds.shm_perm.__key << std::endl;
        printf("shm __key: 0x%x", shmds.shm_perm.__key);
    }

    shmdt(shmaddr);
    // log(Debug,"detach shm done,shmaddr:0x%x",shmaddr);
    shmctl(shmid, IPC_RMID, nullptr);
    // log(Debug,"destory shm done,shmaddr:0x%x",shmaddr);
    close(fd);
    return 0;
}
