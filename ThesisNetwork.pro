#-------------------------------------------------
#
# Project created by QtCreator 2011-02-20T16:54:14
#
#-------------------------------------------------

QT       += core \
            network \
            gui

TARGET = ThesisNetwork
CONFIG   += app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    udpserver.cpp \
    server.cpp \
    listdevices.cpp \
    mapper.cpp \
    temp/xmlreader.cpp \
    temp/sensorxy.cpp \
    temp/handledevice.cpp \
    temp/controller.cpp \
    temp/connecteddevice.cpp \
    temp/button.cpp \
    temp/allfiles.cpp \
    temp/allconnected.cpp \
    temp/usablecontrollers.cpp \
    nodesocket.cpp \
    node.cpp

HEADERS += \
    udpserver.h \
    server.h \
    listdevices.h \
    mapper.h \
    temp/xmlreader.h \
    temp/sensorxy.h \
    temp/handledevice.h \
    temp/controller.h \
    temp/connecteddevice.h \
    temp/button.h \
    temp/allfiles.h \
    temp/allconnected.h \
    temp/usablecontrollers.h \
    nodesocket.h \
    node.h

#DEFINES += _WIN32_WINNT="0x0501"
#DEFINES += _WIN32_WINDOWS="0x0501"
