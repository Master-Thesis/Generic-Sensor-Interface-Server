#include <QApplication>
#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include "wiimote/run.h"
#define _WIN32_WINNT 0x0501   // Identify this as a Windows XP application.  This is necessary
                              //    to pull in RawInput (which is an XP exclusive)
#include "temp/usablecontrollers.h"
#include "udpserver.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    Run *thread = new Run(NULL);
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    QApplication app(argc, argv);

    UsableControllers controllers;

    Server server;
    server.show();

    return server.exec();
}
