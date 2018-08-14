#include <memory>

#include <ListenHadler.h>
#include <PollerEvent.h>
#include <ClientHandler.h>
#include <EventLoop.h>
#include <Socket.h>
#include <Log.h>

void moxie::ListenHadler::Process(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
    LOGGER_TRACE("Begin ListenHadler Process!");
    if (event->ValatileErrorEvent() || event->ValatileCloseEvent()) {
        loop->Delete(event);
        ::close(event->GetFd());
        return ;
    }

    if (event->ValatileWriteEvent()) {
        event->DisableWrite();
        assert(loop->Modity(event));
    }

    if (event->ValatileReadEvent()) {
        DoListen(event, loop);
    }
}

void moxie::ListenHadler::DoListen(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
    LOGGER_TRACE("Begin ListenHadler DoListen!");
    int event_fd = event->GetFd();
begin:
    int ret = Socket::Accept(event_fd, true);
    if (ret < 0) {
        if (errno == EINTR) {
            goto begin;
        } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return;
        } else {
            loop->Delete(event);
            ::close(event->GetFd());
            return;
        }
    }

    std::shared_ptr<PollerEvent> client = std::make_shared<PollerEvent>(ret, kReadEvent);
    if (!client) {
        ::close(ret);
        LOGGER_ERROR("Build client shared_ptr error!");
        return;
    }

    client->DisableWrite();

    if (!loop->Register(client, std::make_shared<ClientHandler>())) {
        ::close(ret);
        return;
    }
}
