#-------------------------------------------------
#
# Project created by QtCreator 2011-02-20T16:54:14
#
#-------------------------------------------------

QT       += core gui\
            network \
            #gui

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
    node.cpp \
    wiimote/wiimote.cpp \
    wiimote/run.cpp

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
    node.h \
    wiimote/winuser.h \
    wiimote/winddk.h \
    wiimote/wiimote_state.h \
    wiimote/wiimote_common.h \
    wiimote/wiimote.h \
    wiimote/setupapi.h \
    wiimote/run.h

#DEFINES += _WIN32_WINNT="0x0501"
#DEFINES += _WIN32_WINDOWS="0x0501"

LIBS += libsetupapi \
    libhid \
    libuser32
#INCLUDEPATH += "C:\\Qt\\2010.05\\mingw\\include" \

LIBS +=  -luser32 -L"C:\\Qt\\2010.05\\mingw\\lib"

LIBS += "C:\Qt\2010.05\mingw\lib\libwinmm.a"

LIBS += "C:\Qt\2010.05\mingw\lib\libhid.a"

LIBS += "C:\Qt\2010.05\mingw\lib\libsetupapi.a"

LIBS += "C:\Qt\2010.05\mingw\lib\libuser32.a"

LIBS += "C:\WinDDK\7600.16385.1\lib\win7\i386\hid.lib"
