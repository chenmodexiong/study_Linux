#include "Mystdio.h"
#include <unistd.h> 
int main()
{
    //_FILE* fp=_fopen("test.txt","w");
    _FILE* fp=_fopen("test.txt","a");
    //_FILE* fp=_fopen("test.txt","r");
    
    if(fp==NULL) return 1;
    const char* msg="hello world\n";
    _fwrite(fp,msg,strlen(msg));
    //_fflush(fp);
    
    sleep(5);

    _fclose(fp); 
    return 0;
}


