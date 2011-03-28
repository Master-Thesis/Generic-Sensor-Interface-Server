#ifndef LISTDEVICES_H
#define LISTDEVICES_H

#include <QObject>
#include <QIODevice>

class ListDevices
{
public:
    ListDevices();
    QByteArray ListAllInfo();
};

#endif // LISTDEVICES_H
