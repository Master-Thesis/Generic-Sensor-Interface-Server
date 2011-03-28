#include <QApplication>
#include <QtNetwork>
#include <QDebug>
#include <iostream>

#include "temp/usablecontrollers.h"
#include "udpserver.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    // Check all available IPv4 addresses of the machine and exclude personal IP's and Localhost
//    // Under the assumption the machine is incorporated in a network
//    // Use the first found as IP-Address
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//    QHostAddress cAddress;
//    for (int i = 0; i < ipAddressesList.size(); ++i) {
//        if (ipAddressesList.at(i).toIPv4Address() &&
//            ipAddressesList.at(i) != QHostAddress::LocalHost &&
//            !ipAddressesList.at(i).toString().startsWith("169"))
//        {
//            cAddress = ipAddressesList.at(i);
//            qDebug() <<  cAddress.toString() << endl;
//            break;
//        }
//        //end if
//    }
//    //end for

//    int input;
//    cin >> input;
//    cout << "You said: " << input << endl;

    UsableControllers controllers;

    Server server;
    server.show();

    //QTimer::singleShot(5000, &a, SLOT(quit())); //stop after 5 second
    return server.exec();
}
