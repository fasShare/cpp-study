TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += \
    Epoll.cpp \
    Timestamp.cpp \
    Socket.cpp \
    NetAddress.cpp \
    Condition.cpp \
    EventLoop.cpp \
    ListenHadler.cpp \
    ClientHandler.cpp \
    Buffer.cpp \
    echo.cpp

HEADERS += \
    Epoll.h \
    Log.h \
    Timestamp.h \
    PollerEvent.h \
    Socket.h \
    NetAddress.h \
    SigIgnore.h \
    MutexLocker.h \
    Mutex.h \
    Condition.h \
    EventLoop.h \
    Handler.h \
    ListenHadler.h \
    ClientHandler.h \
    Buffer.h
