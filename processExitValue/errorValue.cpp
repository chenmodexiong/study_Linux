#include <stdio.h>
#include <string.h>

int main()
{
    for(int i=0;i<134;i++)
    {
        if(strerror(i))
        {
            printf("%d : %s\n",i,strerror(i));
        }
    }
    return 0;
}



