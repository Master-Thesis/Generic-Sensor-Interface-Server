#include "allfiles.h"

allFiles::allFiles()
{
    qDebug() << "allFiles::allFiles() entered";
    openAll();
}

//Make a list of all controllers out of the XML-files
QList<Controller> allFiles::openAll()
{

    QDir dir("c://xml/");
    QStringList filters;
    filters << "*.xml";
    Controller controller;
    Controller *tempController;
    tempController = &controller;


    foreach ( QString file, dir.entryList(filters, QDir::Files) ){
        XMLReader t;
        QString filePath = "c://xml/" + file;
               // std::cout << file.toStdString() << std::endl;
        controller = t.OpenXMLFile(filePath);
       // tempController->printAll();
        controllers.append(controller);
        //cout << file.toStdString() << endl;

    }

    return controllers;
}

void allFiles::addController(Controller *newController)
{
    //controllers.append(*newController);

        //numberOfButtons++;
}

void allFiles::printAllControllersDetailInfo(){
    int i = 0;
    while(i<controllers.size()){
        controllers[i].printAll();
        i++;
    }
}

QString allFiles::findNameWithVidPid(int vid, int pid){
    QString name = "Name Unknown";
    int i = 0;
    while(i<controllers.size()){
        if(controllers[i].getVendorID() == vid && controllers[i].getProductID() == pid){
            name = controllers[i].getDescription();
        }
        i++;
    }
    return name;
}

int allFiles::findIndexWithVidPid(int vid, int pid){
    int index = 0;
    int i = 0;
    while(i<controllers.size()){
        if(controllers[i].getVendorID() == vid && controllers[i].getProductID() == pid){
            index = i;
        }
        i++;
    }
    return index;
}
