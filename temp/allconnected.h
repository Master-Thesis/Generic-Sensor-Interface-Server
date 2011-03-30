#ifndef ALLCONNECTED_H
#define ALLCONNECTED_H

#include "connecteddevice.h"
#include <QList>

#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <QString>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include "allfiles.h"
#include <QDebug>


#ifdef UNICODE
#define QStringToTCHAR(x)     (wchar_t*) x.utf16()
#define PQStringToTCHAR(x)    (wchar_t*) x->utf16()
#define TCHARToQString(x)     QString::fromUtf16((x))
#define TCHARToQStringN(x,y)  QString::fromUtf16((x),(y))
#else
#define QStringToTCHAR(x)     x.local8Bit().constData()
#define PQStringToTCHAR(x)    x->local8Bit().constData()
#define TCHARToQString(x)     QString::fromLocal8Bit((x))
#define TCHARToQStringN(x,y)  QString::fromLocal8Bit((x),(y))
#endif

class AllConnected
{
public:
    AllConnected();
    QList<connectedDevice> getAllConnectedList(){return connected;}
    unsigned long long ConvertStringToHex(QString hexVal);

private:
    void ListAllInfo();
    QList<connectedDevice> connected;
};

#endif // ALLCONNECTED_H
