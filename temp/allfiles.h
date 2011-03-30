#ifndef ALLFILES_H
#define ALLFILES_H

#include "controller.h"
#include <QList>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <QString>
#include <cstdlib>
#include <string>
#include <QDir>
#include "xmlreader.h"
using namespace std;

class allFiles
{
public:
    allFiles();
    QList<Controller> openAll();
    void addController(Controller *newController);
    void printAllControllersDetailInfo();
    QString findNameWithVidPid(int vid, int pid);
    int findIndexWithVidPid(int vid, int pid);
    QList<Controller> getAllControllersList(){return controllers;}
    QList<Controller> findController(const int buttons, const int xy, const int vector);
    QList<Controller> getControllerWithString(const QString description);

private:
    QList<Controller> controllers;
};



#endif // ALLEFILES_H
