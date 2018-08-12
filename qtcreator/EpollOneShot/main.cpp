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
#define TMP_BUF_SIZE 1024
#endif

#ifndef THREAD_NUM
#define THREAD_NUM 4
#endif

static void *WorkFunc() {
    int accept_sd = 0;
    moxie::Socket listenfd(AF_INET, SOCK_STREAM, 0);
    if (listenfd.getSocket() < 0) {
        std::cout << "socket : " << strerror(errno) << std::endl;
        return reinterpret_cast<void *>(-1);
    }

    int flag = 1;
    if (0 > setsockopt(listenfd.getSocket(), SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag))) {
        std::cout << "setsockopt:" << strerror(errno) << std::endl;
        return reinterpret_cast<void *>(-1);
    }

    if (0 > setsockopt(listenfd.getSocket(), SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag))) {
        std::cout << "setsockopt:" << strerror(errno) << std::endl;
        return reinterpret_cast<void *>(-1);
    }

    moxie::NetAddress addr(AF_INET, 8899, "127.0.0.1");
    listenfd.setNoBlocking();
    listenfd.setExecClose();

    if (!(listenfd.bind(addr) && listenfd.listen(200))) {
        return reinterpret_cast<void *>(-1);
    }

    moxie::Epoll *loopepoll = new moxie::Epoll();

    moxie::PollerEvent le;
    le.event = moxie::kReadEvent;
    le.fd = listenfd.getSocket();

    if (!loopepoll->EventsAdd(&le)) {
        return reinterpret_cast<void *>(-1);
    }

    std::vector<moxie::PollerEvent> events;
    char buf[TMP_BUF_SIZE];
    while (true) {
        loopepoll->Loop(events, 3000);

        for (size_t index = 0; index < events.size(); ++index) {
            moxie::PollerEvent &event = events[index];
            if (event.fd == listenfd.getSocket()) {
                if (event.event & moxie::kReadEvent) {
                    int client = accept4(event.fd, nullptr, nullptr, SOCK_NONBLOCK | SOCK_CLOEXEC);
                    if (client < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            std::cout << "accept[" << std::this_thread::get_id() << "] : " << strerror(errno) << std::endl;
                            continue;
                        } else {
                            std::cout << "accept[" << std::this_thread::get_id() << "] : " << strerror(errno) << std::endl;
                            return reinterpret_cast<void *>(-1);
                        }
                    } else {
                        accept_sd++;
                        le.event = moxie::kReadEvent;
                        le.fd = client;

                        loopepoll->EventsAdd(&le);
                        std::cout << "accept[" << std::this_thread::get_id() << "] : " << "New TcpConnection!" << std::endl;
                    }
                }
                continue;
            } else {
                ssize_t ret = read(event.fd, buf, TMP_BUF_SIZE - 1);
                if (ret < 0) { // 失败
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        continue;
                    } else {
                        loopepoll->EventsDel(&event);
                        ::close(event.fd);
                    }
                } else if (ret == 0) { // 关闭
                    std::cout << "read:" << strerror(errno) << std::endl;
                    loopepoll->EventsDel(&event);
                    ::close(event.fd);
                } else {
                    buf[ret] = 0;
                    std::cout << "buf:" << buf << std::endl;
                }

            }
        }

        std::cout <<  "清空历史事件 accept client [" << accept_sd << "]" << std::endl;
        events.clear();
    }

    return reinterpret_cast<void *>(0);
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
