#include <stdexcept>

#include "Utility.h"

#define BUF_SIZE 250

#ifdef _WIN32

#include <windows.h>

std::string Utility::getExecutablePath(){
    char buf[BUF_SIZE];
    if(GetModuleFileNameA(NULL, buf, BUF_SIZE) != 0){
        std::string s1 = buf;
        return s1.substr(0, s1.find_last_of("\\/")) + '\\';
    }
    throw std::runtime_error("Error when extracting the path to your .exe file.");
}

#elif __linux__

#include <unistd.h>

std::string Utility::getExecutablePath(){
    char buf[BUF_SIZE];
    if(readlink("/proc/self/exe", buf, sizeof(buf)) != -1){
        std::string s1 = buf;
        return s1.substr(0, s1.find_last_of("\\/")) + '/';
    }
    throw std::runtime_error("Error when extracting the path to your executable.");
}

#elif __APPLE__

#include <mach-o/dyld.h>

std::string Utility::getExecutablePath(){
    char buf[BUF_SIZE];
    uint32_t bufSize = sizeof(buf);
    if(_NSGetExecutablePath(buf, &bufSize) != -1){
        std::string s1 = buf;
        return s1.substr(0, s1.find_last_of("\\/")) + '/';
    }
    throw std::runtime_error("Error when extracting the path to your executable.");
}

#else
#error The operating system is not supported!
#endif
