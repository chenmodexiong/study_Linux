#include "Mystdio.h" 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_MODE 0666

_FILE* _fopen(const char *filename,const char* flag)
{
    int f=0;
    int fd=-1;
    if(strcmp(flag,"w")==0) 
    {
        f=(O_CREAT|O_WRONLY|O_TRUNC);
        fd=open(filename,f,FILE_MODE);
    }
    else if(strcmp(flag,"a")==0) 
    {
        f=(O_CREAT|O_WRONLY|O_APPEND);
        fd=open(filename,f,FILE_MODE);
    }
    else if(strcmp(flag,"r")==0) 
    {
        f=O_RDONLY;
        fd=open(filename,f,FILE_MODE);
    }
    else return NULL;

    if(fd==-1)
        return NULL;
    _FILE *fp=(_FILE*)malloc(sizeof(_FILE)); 
    if(fp==NULL) return NULL;
    fp->fileno =fd;
    return fp;
}
int _fwrite(_FILE *fp,const char* s,int len)
{
    return write(fp->fileno,s,len);
}
void _fclose(_FILE *fp)
{
    if(fp==NULL) return; 
    close(fp->fileno); 
    free(fp);    
}
