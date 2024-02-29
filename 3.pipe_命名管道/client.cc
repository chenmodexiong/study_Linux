#include "comm.hpp"

int main()
{
    int fd = open(FIFO_FILE, O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        exit(FIFO_OPEN_ERROR);
    }
    std::string line;
    while (true)
    {
        std::cout << "Please Enter@ ";
        getline(std::cin,line);
        write(fd, line.c_str(), line.size());
    }
    close(fd);
    return 0;
}