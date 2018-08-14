#ifndef MOXIE_LISTENHADLER_H
#define MOXIE_LISTENHADLER_H
#include <Handler.h>

namespace moxie {

class ListenHadler : public Handler {
public:
    virtual ~ListenHadler() {}
    virtual void Process(const std::shared_ptr<PollerEvent>& event, EventLoop *loop);
    void DoListen(const std::shared_ptr<PollerEvent>& event, EventLoop *loop);
};

}
#endif // MOXIE_LISTENHADLER_H
