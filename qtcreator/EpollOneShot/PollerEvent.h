#ifndef MOXIE_POLLEREVENT_H
#define MOXIE_POLLEREVENT_H
#include <iostream>
#include <sys/epoll.h>
#include <sys/poll.h>

namespace moxie {

const uint32_t kNoneEvent = 0;
const uint32_t kReadEvent = EPOLLIN | EPOLLPRI;
const uint32_t kWriteEvent = EPOLLOUT;
const uint32_t kOneShot = EPOLLONESHOT;

struct PollerEvent {
    int fd;
    uint32_t event;
};

}

#endif // MOXIE_POLLEREVENT_H
