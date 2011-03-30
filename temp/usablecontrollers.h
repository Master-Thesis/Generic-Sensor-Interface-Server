#ifndef USABLECONTROLLERS_H
#define USABLECONTROLLERS_H

#include <QList>
#include "supporteddevices.h"
#include "connecteddevice.h"
#include "allconnected.h"

class UsableControllers
{
public:
    UsableControllers();
    static QList<Controller> getList() {return usableControllers;}
    static QByteArray printAllWithDetails();
    static QByteArray printAllShortList();


private:
    static QList<Controller> usableControllers;
    void init();
};

#endif // USABLECONTROLLERS_H
