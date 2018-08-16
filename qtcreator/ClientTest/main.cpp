#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <pthread.h>

#include <iostream>
#include <thread>

#include <Epoll.h>
#include <Socket.h>
#include <NetAddress.h>

#ifndef TMP_BUF_SIZE
#define TMP_BUF_SIZE 128
#endif

#ifndef THREAD_NUM
#define THREAD_NUM 4
#endif

static void WorkFunc() {
    int in_not_equal_ret = 0;
    int ok_connection = 0;
    moxie::Socket listenfd(AF_INET, SOCK_STREAM, 0);
    if (listenfd.getSocket() < 0) {
        std::cout << "socket : " << strerror(errno) << std::endl;
        return;
    }
    moxie::NetAddress addr(AF_INET, 8899, "127.0.0.1");
    if (!listenfd.connect(addr)) {
        return ;
    }

    while (ok_connection <= 10000000) {
        char *sendstr = "HelloWorld!";
        char writebuf[TMP_BUF_SIZE];

        int ret = write(listenfd.getSocket(), sendstr, strlen(sendstr));
        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
        }

        int in = read(listenfd.getSocket(), writebuf, TMP_BUF_SIZE - 1);
        if (in < 0) {
            if (errno == EINTR) {
                continue;
            }
        }

        if (in > 0) {
            writebuf[in] = 0;
            if (in = ret) {
                ok_connection++;
                //std::cout << "recv:" << writebuf << " [" << in_not_equal_ret << "]" << std::endl;
            } else {
                in_not_equal_ret++;
                //std::cout << "in != ret" << std::endl;
            }
        }
    }
    std::cout << "ok_connection = [" << ok_connection << "]" << " in_not_equal_ret = [" << in_not_equal_ret << "]" << std::endl;
    listenfd.close();
}

int main() {
    std::vector<std::thread> ths;

    for (size_t index = 0; index < THREAD_NUM; ++index) {
        ths.push_back(std::thread(WorkFunc));
    }

    for (size_t index = 0; index < ths.size(); ++index) {
        ths[index].join();
    }

    std::cout << "Main(" << THREAD_NUM << ") Exit!" << std::endl;

    return 0;
}
