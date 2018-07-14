#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void* threadFuncChdir(void *data) {
    if (-1 == chdir("/home/fas")) {
        std::cout << "In func " << __func__ << " chdir error : " << strerror(errno) << std::endl;
        return nullptr;
    }
    char str[255];
    memset(str, 0, sizeof str);

    if (nullptr == getcwd(str, 255 - 1)) {
        std::cout << "In func " << __func__  <<  " getcwd error : " << strerror(errno) << std::endl;
        return nullptr;
    }
    std::cout << "In func " << __func__  <<  " getcwd:" << str << std::endl;
    sleep(20);

    return nullptr;
}

void* threadFuncPwd(void *data) {
    sleep(10);
    char str[255];
    memset(str, 0, sizeof str);
    if (nullptr == getcwd(str, 255 - 1)) {
        std::cout << "In func " << __func__  << " getcwd error : " << strerror(errno) << std::endl;
        return nullptr;
    }
    std::cout << "In func " << __func__  <<  " getcwd:" << str << std::endl;
    sleep(10);
    return nullptr;
}

int main() {
    char str[255];
    memset(str, 0, sizeof str);
    if (nullptr == getcwd(str, 255 - 1)) {
        std::cout << "In func " << __func__  << " getcwd error : " << strerror(errno) << std::endl;
        return -1;
    }
    std::cout << "In func " << __func__  <<  " getcwd:" << str << std::endl;
    pthread_t tidpwd, tidchdir;
    pthread_create(&tidpwd, nullptr, threadFuncPwd, nullptr);
    pthread_create(&tidchdir, nullptr, threadFuncChdir, nullptr);
    std::cout << "create threadpwd:" << tidpwd << " threadchdir:" << tidchdir << std::endl; 
    pthread_join(tidchdir, nullptr);
    pthread_join(tidpwd, nullptr);

    memset(str, 0, sizeof str);
    if (nullptr == getcwd(str, 255 - 1)) {
        std::cout << "In func " << __func__  << " getcwd error : " << strerror(errno) << std::endl;
        return -1;
    }
    std::cout << "In func " << __func__  <<  " getcwd:" << str << std::endl;
    return 0;
}
