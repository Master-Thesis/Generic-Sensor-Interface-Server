#ifndef SUPPORTEDDEVICES_H
#define SUPPORTEDDEVICES_H

#include "controller.h"
#include "xmlreader.h"

#include <QList>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <QString>
#include <cstdlib>
#include <string>
#include <QDir>

class SupportedDevices
{
public:
    static SupportedDevices* instance();
    static void drop();
    static QList<Controller> openAll();
    static void printAllDevicesDetailInfo();
    static QString findNameWithVidPid(int vid, int pid);
    static int findIndexWithVidPid(int vid, int pid);
    static QList<Controller> getAllDevicesList(){return devices;}
    static QList<Controller> findDevice(const int buttons, const int xy, const int vector);
    static QList<Controller> getDeviceWithString(const QString description);
    static QByteArray printDevicesWithString(const QString description);

private:
    SupportedDevices();
    ~SupportedDevices();

    static QList<Controller> devices;
};



#endif // SUPPORTEDDEVICES_H
