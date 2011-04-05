#include "supporteddevices.h"

#include <QMutex>

static QMutex mutex;

SupportedDevices* SupportedDevices::m_supdevs = 0;

QList<Controller> SupportedDevices::devices;


SupportedDevices::SupportedDevices()
{
    qDebug() << "SupportedDevices::allFiles() entered";
    openAll();
}

SupportedDevices::~SupportedDevices()
{
}

SupportedDevices* SupportedDevices::instance()
{
    if(!m_supdevs)
    {
        mutex.lock();

        if(!m_supdevs)
            m_supdevs = new SupportedDevices();

        mutex.unlock();
    }

    return m_supdevs;
}

void SupportedDevices::drop()
{
    mutex.lock();
    delete m_supdevs;
    m_supdevs = 0;
    mutex.unlock();
}

//Make a list of all controllers out of the XML-files
QList<Controller> SupportedDevices::openAll()
{

    QDir dir("c://xml/");
    QStringList filters;
    filters << "*.xml";
    Controller controller;
    Controller *tempController;
    tempController = &controller;


    foreach ( QString file, dir.entryList(filters, QDir::Files) )
    {
        XMLReader t;
        QString filePath = "c://xml/" + file;
        controller = t.OpenXMLFile(filePath);
       // tempController->printAll();
        devices.append(controller);

    }

    return devices;
}

void SupportedDevices::printAllDevicesDetailInfo()
{
    int i = 0;
    while(i<devices.size()){
        devices[i].printAll();
        i++;
    }
}

QString SupportedDevices::findNameWithVidPid(int vid, int pid)
{
    QString name = "Name Unknown";
    int i = 0;
    while(i<devices.size()){
        if(devices[i].getVendorID() == vid && devices[i].getProductID() == pid){
            name = devices[i].getDescription();
        }
        i++;
    }
    return name;
}

int SupportedDevices::findIndexWithVidPid(int vid, int pid)
{
    int index = 0;
    int i = 0;
    while(i<devices.size()){
        if(devices[i].getVendorID() == vid && devices[i].getProductID() == pid){
            index = i;
        }
        i++;
    }
    return index;
}

QList<Controller> SupportedDevices::findDevice(const int buttons, const int xy, const int vector)
{
    QList<Controller> con;
    int i = 0;
    while(i<devices.size()){
        if((devices[i].getNumberOfButtons() >= buttons) && (devices[i].getNumberOfXY() >= xy)  && (devices[i].getNumberOfVectors() >= vector)){
            con.append(devices[i]);
        }
        i++;
    }
    return con;

}

QList<Controller> SupportedDevices::getDeviceWithString(const QString description)
{

    QStringList desList;
    desList = description.toLower().split(',');
    QStringList desList2;
    int buttons = 0;
    int xy = 0;
    int vector = 0;

    int i = 0;
    while(i<desList.size()){
        desList2 = desList.at(i).split(' ');
        if(desList2.at(0) == "b"){
            buttons = desList2.at(1).toInt();
        }
        if(desList2.at(0) == "p"){
            xy = desList2.at(1).toInt();
        }
        if(desList2.at(0) == "v"){
            vector = desList2.at(1).toInt();
        }
        i++;
    }

  return findDevice(buttons, xy, vector);

}

QByteArray SupportedDevices::printDevicesWithString(const QString description)
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    QList<Controller> list = getDeviceWithString(description);

    for(int i = 0; i < list.size(); i++)
    {
        outStream << i << ":\t" << list[i].getDescription() << "\n";
    }

    outStream.flush();
    return *outArray;
}
