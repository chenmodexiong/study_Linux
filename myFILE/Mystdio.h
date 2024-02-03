//#pragma once 
#ifndef __MYSTDIO_H__
#define __MYSTDIO_H__ 

#include <string.h>

typedef struct IO_FILE
{
   int fileno;
    
}_FILE;

_FILE* _fopen(const char *filename,const char* flag);
int _fwrite(_FILE *fp,const char* s,int len);
void _fclose(_FILE *fp);

#endif 
