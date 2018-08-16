TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -static

INCLUDEPATH += /opt/openssl_1_0_2p/include
LIBS += -L/opt/openssl_1_0_2p/lib  -lssl -lcrypto -ldl

SOURCES += main.cpp \
    sslclient.cpp
