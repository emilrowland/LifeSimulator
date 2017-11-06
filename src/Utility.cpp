#include "Utility.h"

#define BUF_SIZE 150

#ifdef _WIN32

#include <windows.h>

std::string Utility::getExecuteblePath(){
    char buf[BUF_SIZE];
    GetModuleFileNameA(NULL, buf, BUF_SIZE);
    std::string s1 = buf;
    return s1.substr(0, s1.find_last_of("\\/")) + '\\';
}

#elif __linux__

#include <unistd.h>

std::string Utility::getExecuteblePath(){
    char buf[BUF_SIZE];
    readlink("/proc/self/exe", buf, sizeof(buf));
    std::string s1 = buf;
    return s1.substr(0, s1.find_last_of("\\/")) + '/';
}

#elif __APPLE__

#include <mach-o/dyld.h>

std::string Utility::getExecuteblePath(){
    char buf[BUF_SIZE];
    uint32_t bufSize = sizeof(buf);
    _NSGetExecutablePath(buf, &bufSize);
    std::string s1 = buf;
    return s1.substr(0, s1.find_last_of("\\/")) + '/';
}

#else
#error The operating system is not supported!
#endif
