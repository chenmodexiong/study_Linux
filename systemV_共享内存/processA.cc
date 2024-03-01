#include "comm.hpp"

extern Log log;
int main()
{
    int shmid = CreateShm();
    // log(Debug,"create shm done");
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    // log(Debug,"attach shm done,shmaddr:0x%x",shmaddr);
    struct shmid_ds shmds;
    // 一旦挂接了共享内存，有人写入数据则立马就可以看到，不需要经过系统调用
    // ipc code
    while (true)
    {
        std::cout << "client say@" << shmaddr << std::endl; // 直接访问共享内存
        sleep(1);

        shmctl(shmid, IPC_STAT, &shmds);
        std::cout << "shm size: " << shmds.shm_segsz << std::endl;
        std::cout << "shm natth: " << shmds.shm_nattch << std::endl;
        //std::cout << "shm __key: " << shmds.shm_perm.__key << std::endl;
        printf("shm __key: 0x%x",shmds.shm_perm.__key);
    }

    shmdt(shmaddr);
    // log(Debug,"detach shm done,shmaddr:0x%x",shmaddr);
    shmctl(shmid, IPC_RMID, nullptr);
    // log(Debug,"destory shm done,shmaddr:0x%x",shmaddr);

    return 0;
}
