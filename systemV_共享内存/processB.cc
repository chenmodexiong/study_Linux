#include "comm.hpp"

int main()
{
    int shmid = GetShm();
    // log(Debug, "create shm done");
    char *shmaddr = (char *)shmat(shmid, nullptr, 0);
    // log(Debug, "attach shm done,shmaddr:0x%x", shmaddr);

    //一旦挂接了共享内存，直接将它拿来就可以用，不需要缓冲区
    //ipc code
    while(true)
    {
        // char buffer[1024];
        std::cout<<"Please Enter@";
        fgets(shmaddr,4096,stdin);
        // memcpy(shmaddr,buffer,strlen(buffer)+1);
    }

    shmdt(shmaddr);
    // log(Debug, "detach shm done,shmaddr:0x%x", shmaddr);

    return 0;
}