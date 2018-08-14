#include <unistd.h>

#include <ClientHandler.h>
#include <EventLoop.h>
#include <Log.h>

moxie::ClientHandler::ClientHandler() :
    readBuf_(512),
    writeBuf_(512) {
}

void moxie::ClientHandler::Process(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
    LOGGER_TRACE("Begin ClientHandler Process!");
    if (event->ValatileErrorEvent() || event->ValatileCloseEvent()) {
        loop->Delete(event);
        ::close(event->GetFd());
        return ;
    }

    if (event->ValatileWriteEvent()) {
        DoWrite(event, loop);
        if (writeBuf_.readableBytes() <= 0) {
            event->DisableWrite();
            loop->Modity(event);
        }
    }

    if (event->ValatileReadEvent()) {
        DoRead(event, loop);
        // FIXME : write condition
        if (readBuf_.readableBytes() > 0) {
            writeBuf_.append(readBuf_.peek(), readBuf_.readableBytes());
            readBuf_.retrieveAll();
            event->EnableWrite();
            loop->Modity(event);
        }
    }
}

void moxie::ClientHandler::DoRead(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
    LOGGER_TRACE("Begin ClientHandler DoRead!");
    int event_fd = event->GetFd();
    char buf[128];
    while (true) {
        int ret = read(event_fd, buf, 127);
        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            } else {
                loop->Delete(event);
                ::close(event_fd);
                return;
            }
        }

        if (ret == 0) {
            loop->Delete(event);
            ::close(event_fd);
            return;
        }

        readBuf_.append(buf, ret);
    }
}

void moxie::ClientHandler::DoWrite(const std::shared_ptr<PollerEvent>& event, EventLoop *loop) {
    LOGGER_TRACE("Begin ClientHandler DoWrite!");
    int event_fd = event->GetFd();
    size_t len = writeBuf_.readableBytes();
    while (len > 0) {
        int ret = write(event_fd, writeBuf_.peek(), len);
        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            } else {
                loop->Delete(event);
                ::close(event_fd);
                return;
            }
        }

        if (ret == 0) {
            loop->Delete(event);
            ::close(event_fd);
            return;
        }

        len -= ret;
        writeBuf_.retrieve(ret);
    }
}
