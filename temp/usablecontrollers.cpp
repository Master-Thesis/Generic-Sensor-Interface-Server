#include "usablecontrollers.h"

QList<Controller> UsableControllers::usableControllers;

UsableControllers::UsableControllers()
{
    init();
}

void UsableControllers::init()
{
    qDebug() << "UsableControllers::init() entered";

    SupportedDevices supported;
    AllConnected connected;

    qDebug() << "UsableControllers::init() start comparison";

    int size = connected.getAllConnectedList().size();
    int size2 = SupportedDevices::instance()->getAllDevicesList().size();
    qDebug() << "connected size: " << size;
    qDebug() << "supported size: " << size2;
    int i = 0;
    while(i < size){
        int vendorID = connected.getAllConnectedList()[i].getVendorID();
        int productID = connected.getAllConnectedList()[i].getProductID();
        int j = 0;
        while(j<size2){
            int vendorID2 = supported.getAllControllersList()[j].getVendorID();
            int productID2 = supported.getAllControllersList()[j].getProductID();
//            qDebug() << "------COMP-----";
//            qDebug() << "vid1: " << QString::number(vendorID,16);
//            qDebug() << "vid2: " << QString::number(vendorID2,16);
//            qDebug() << "pid1: " << QString::number(productID,16);
//            qDebug() << "pid1: " << QString::number(productID2,16);
//            qDebug() << "///////////////";
            if(vendorID == vendorID2 && productID == productID2){
                usableControllers.append(supported.getAllControllersList()[j]);
            }
            j++;
        }
        i++;
    }
    qDebug() << "connected + supported size: " << usableControllers.size();
}

QByteArray UsableControllers::printAllWithDetails()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "Trying to print supported controllers, size of the list = " << usableControllers.size();
    int i = 0;
    while(i<usableControllers.size()){
        outStream << "Nr: " << i;
        outStream << usableControllers[i].printAll();
        i++;
    }

    outStream.flush();
    return *outArray;
}

QByteArray UsableControllers::printAllShortList()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    int i = 0;
    while(i<usableControllers.size()){
        outStream << i << ":\t" << usableControllers[i].getDescription() << "\n";
        i++;
    }

    outStream.flush();
    return *outArray;
}


