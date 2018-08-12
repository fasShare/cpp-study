TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += main.cpp \
    Epoll.cpp \
    Timestamp.cpp \
    Socket.cpp \
    NetAddress.cpp

HEADERS += \
    Epoll.h \
    Log.h \
    Timestamp.h \
    PollerEvent.h \
    Socket.h \
    NetAddress.h \
    main_copy.cpp1
