#pragma once

#include <iostream>
#include <stdarg.h>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>

#define SIZE 1024

#define Info 0
#define Debug 1
#define Warning 2
#define Error 3
#define Fatal 4

#define Screen 1
#define Onefile 2
#define Classfile 3

#define LogFile "log.txt"
class Log
{
public:
    Log()
    {
        printMethod = Screen;
        path = "./log/";
    }
    void Enable(int method)
    {
        printMethod = method;
    }
    std::string levelToString(int level)
    {
        switch (level)
        {
        case Info:
            return "Info";
        case Debug:
            return "Debug";
        case Warning:
            return "Warning";
        case Error:
            return "Error";
        case Fatal:
            return "Fatal";
        default:
            return "None";
        }
    }

    // void LogMessage(int level, const char *format, ...)
    // {
    //     time_t t = time(nullptr);
    //     struct tm *ctime = localtime(&t);
    //     char defaultbuffer[SIZE];
    //     snprintf(defaultbuffer, sizeof(defaultbuffer), "[%s][%d-%d-%d %d:%d:%d]", levelToString(level).c_str(),
    //              ctime->tm_year + 1900, ctime->tm_mon + 1, ctime->tm_mday, ctime->tm_hour, ctime->tm_min, ctime->tm_sec);
    //     // 日志=默认部分(日志等级,日志内容,文件名称,行号)+自定义部分(可变参数部分)
    //     va_list s;
    //     va_start(s, format);
    //     char rightbuffer[SIZE * 2];
    //     vsnprintf(rightbuffer, sizeof(rightbuffer), format, s);
    //     va_end(s);
    //     char logtxt[SIZE * 2];
    //     snprintf(logtxt, sizeof(logtxt), "%s %s\n", defaultbuffer, rightbuffer);
    //     printLog(level, logtxt);
    // }
    void printLog(int level, std::string logtxt)
    {
        switch (printMethod)
        {
        case Screen:
            std::cout << logtxt << std::endl;
            break;
        case Onefile:
            printOneFile(LogFile, logtxt);
            break;
        case Classfile:
            printClassfile(level, logtxt);
            break;
        default:
            break;
        }
    }
    void printOneFile(const std::string logname, const std::string &logtxt)
    {
        std::string _logname = path + logname;
        int fd = open(_logname.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (fd < 0)
            return;
        write(fd, logtxt.c_str(), logtxt.size());
        close(fd);
    }
    void printClassfile(int level, const std::string &logtxt)
    {
        std::string filename = LogFile;
        filename += ".";
        filename += levelToString(level); // log.txt.Debug/Warning/Fatal...
        printOneFile(filename, logtxt);
    }
    ~Log() {}
    void operator()(int level, const char *format, ...)
    {
        time_t t = time(nullptr);
        struct tm *ctime = localtime(&t);
        char defaultbuffer[SIZE];
        snprintf(defaultbuffer, sizeof(defaultbuffer), "[%s][%d-%d-%d %d:%d:%d]", levelToString(level).c_str(),
                 ctime->tm_year + 1900, ctime->tm_mon + 1, ctime->tm_mday, ctime->tm_hour, ctime->tm_min, ctime->tm_sec);
        // 日志=默认部分(日志等级,日志内容,文件名称,行号)+自定义部分(可变参数部分)
        va_list s;
        va_start(s, format);
        char rightbuffer[SIZE * 2];
        vsnprintf(rightbuffer, sizeof(rightbuffer), format, s);
        va_end(s);
        char logtxt[SIZE * 2];
        snprintf(logtxt, sizeof(logtxt), "%s %s\n", defaultbuffer, rightbuffer);
        printLog(level, logtxt);
    }

private:
    int printMethod;
    std::string path;
};

// 可变参数列表
//  int sum(int n, ...)
//  {
//      va_list s; //char*
//      va_start(s,n); //从右向左实例化
//      int sum =0;
//      while(n)
//      {
//          sum+=va_arg(s,int);
//          n--;
//      }
//      va_end(s);//s=NULL
//      return sum;
//  }