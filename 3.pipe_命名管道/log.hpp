#pragma once

#include <iostream>
#include <stdarg.h>
void LogMessage(int level, char *format, ...)
{
}

//可变参数列表
// int sum(int n, ...)
// {
//     va_list s; //char*
//     va_start(s,n); //从右向左实例化
//     int sum =0;
//     while(n)
//     {
//         sum+=va_arg(s,int);
//         n--;
//     }
//     va_end(s);//s=NULL
//     return sum;
// }