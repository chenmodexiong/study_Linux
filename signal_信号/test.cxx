#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    while (true)
    {
        cout << "I am a test process,my pid is:" <<getpid()<< endl;
        sleep(1);
    }
    return 0;
}
