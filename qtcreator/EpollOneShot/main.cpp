#include <iostream>

#include <EventLoop.h>
#include <string.h>
#include <Log.h>
#include <Socket.h>
#include <NetAddress.h>
#include <PollerEvent.h>
#include <ListenHadler.h>

using namespace moxie;

int main() {
    EventLoop *loop = new EventLoop();
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        LOGGER_ERROR("socket error : " << strerror(errno));
        return -1;
    }

    Socket::SetExecClose(server);
    Socket::SetNoBlocking(server);

    NetAddress addr(AF_INET, 8899, "127.0.0.1");

    if (!(Socket::Bind(server, addr)
          && Socket::Listen(server, 128))) {
        return -1;
    }

    std::shared_ptr<PollerEvent> event = std::make_shared<PollerEvent>(server, moxie::kReadEvent);
    if (!loop->Register(event, std::make_shared<ListenHadler>())) {
        LOGGER_ERROR("Loop Register Error");
        return -1;
    }

    loop->Loop();

    delete loop;
    return 0;
}
