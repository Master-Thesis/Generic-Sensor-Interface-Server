#include <QApplication>
#include <QtNetwork>
#include <QDebug>
#include <iostream>
#define _WIN32_WINNT 0x0501
#include "temp/usablecontrollers.h"
#include "udpserver.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UsableControllers controllers;

    Server server;
    server.show();

    return server.exec();
}
