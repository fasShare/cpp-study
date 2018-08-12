#ifndef MOXIE_EPOLL_H
#define MOXIE_EPOLL_H
#include <sys/epoll.h>
#include <vector>

#include <Timestamp.h>
#include <PollerEvent.h>

namespace moxie {

class Epoll {
public:
    Epoll();
    ~Epoll();

    bool EventsAdd(const PollerEvent * const events);
    bool EventsMod(const PollerEvent * const events);
    bool EventsDel(const PollerEvent * const events);
    Timestamp Loop(std::vector<PollerEvent> &events, int timeout);

private:
    bool eventCtl(int op, int fd, struct epoll_event* event);
    bool eventAdd(int fd, struct epoll_event* event);
    bool eventDel(int fd, struct epoll_event* event);
    bool eventMod(int fd, struct epoll_event* event);
    int loopWait(struct epoll_event* events, int maxevents, int timeout);

    int epoll_fd_;
    std::vector<struct epoll_event> revents_;
    int maxNum_;
    const int addStep_;
};

}
#endif // MOXIE_EPOLL_H
