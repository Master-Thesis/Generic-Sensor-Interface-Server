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

QList<Controller> allFiles::findController(const int buttons, const int xy, const int vector){
    QList<Controller> con;
    int i = 0;
    while(i<controllers.size()){
        if((controllers[i].getNumberOfButtons() > buttons) && (controllers[i].getNumberOfXY() > xy)){
            con.append(controllers[i]);
        }
        i++;
    }
    return con;

}

QList<Controller> allFiles::getControllerWithString(const QString description){

    QStringList desList;
    desList = description.toLower().split(',');
    QStringList desList2;
    int buttons;
    int xy;
    int vector;

    int i = 0;
    while(i<desList.size()){
        desList2 = desList.at(i).split(' ');
        if(desList2.at(0) == "b"){
            buttons = desList2.at(1).toInt();
        }
        else if(desList2.at(0) == "p"){
            xy = desList2.at(1).toInt();
        }
        i++;
    }

  return findController(buttons, xy, vector);

}
