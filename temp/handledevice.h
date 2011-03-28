#ifndef HANDLEDEVICE_H
#define HANDLEDEVICE_H

#include <QThread>

#include "controller.h"
#include "usablecontrollers.h"

class HandleDevice : public QThread
{
    Q_OBJECT

public:
    HandleDevice(MSG *m, long *result, QObject *parent = 0);

    void run();
    void handleIt(RAWINPUT *raw);
    void handleWinEvent(MSG *m, long *result);

signals:
    void buttonAction(QString stateMessage);

private:
    MSG *m;
    long *result;
};

#endif // HANDLEDEVICE_H
