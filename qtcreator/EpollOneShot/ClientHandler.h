#ifndef MOXIE_CLIENTHANDLER_H
#define MOXIE_CLIENTHANDLER_H
#include <Handler.h>
#include <Buffer.h>
#include <Log.h>

namespace moxie {

class ClientHandler : public Handler{
public:
    ClientHandler();
    virtual ~ClientHandler() { LOGGER_TRACE("~ClientHandler"); }
    virtual void Process(const std::shared_ptr<PollerEvent>& event, EventLoop *loop);
    void DoRead(const std::shared_ptr<PollerEvent>& event, EventLoop *loop);
    void DoWrite(const std::shared_ptr<PollerEvent>& event, EventLoop *loop);

private:
    Buffer readBuf_;
    Buffer writeBuf_;
};

}

#endif // CLIENTHANDLER_H
