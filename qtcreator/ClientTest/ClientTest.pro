TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    Timestamp.cpp \
    Socket.cpp \
    NetAddress.cpp \
    Epoll.cpp

HEADERS += \
    Timestamp.h \
    Socket.h \
    PollerEvent.h \
    NetAddress.h \
    Log.h \
    Epoll.h
