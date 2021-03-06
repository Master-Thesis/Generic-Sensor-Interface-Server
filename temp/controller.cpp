#include "controller.h"

Controller::Controller(QString initDescription,
                       int initVendorID,
                       int initProductID)
{
    description = initDescription;
    vendorID = initVendorID;
    productID = initProductID;
}

void Controller::addButton(Button newButton)
{
    buttons.append(newButton);
}

void Controller::addVector(VectorSensor newVector)
{
    vectors.append(newVector);
}

QByteArray Controller::printButtonListDetails()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "\nList of Buttons:";
    int i = 0;
    while(i < buttons.size())
    {
        buttons[i].printInfo();
        i++;
    }

    outStream.flush();
    return *outArray;
}

QByteArray Controller::printButtonList()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "\nList of Buttons:\n";
    int i = 0;
    while(i < buttons.size())
    {
        outStream << i << "\t" << "Name:\t" << buttons[i].getName() << "\n";
        i++;
    }

    outStream.flush();
    return *outArray;
}

void Controller::addXY(SensorXY newXY)
{
    xySensors.append(newXY);
}

QByteArray Controller::printXYList()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    int i = 0;
    while(i < xySensors.size())
    {
        outStream << "\nList of XY" << i << "\n";
        outStream << xySensors[i].printInfo(i);
        i++;
    }

    outStream.flush();
    return *outArray;
}

QByteArray Controller::printAllDetails()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "Description:\t"   << description;
    outStream << "Type:\t\t"   << type;
    outStream << "VendorID:\t" << QString::number(vendorID, 16);
    outStream << "ProductID:\t" << QString::number(productID, 16);
    outStream << printXYList();
    outStream << printButtonList();
    outStream << "\n**********************************************";

    outStream.flush();
    return *outArray;
}

QByteArray Controller::printAll()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "Description:\t"   << description << "\n";
    outStream << printXYList();
    outStream << printButtonList();
    outStream << printVectorList();
    outStream << "\n**********************************************";

    outStream.flush();
    return *outArray;
}

QByteArray Controller::printButtonInfo()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "\nButtons:";
    outStream << "Format:\t" << getFormatButtons();
    outStream << "Bytes:\t" << getNumberOfBytesButtons();
    //outStream << generalFlagPressed;
    //outStream << formatFlagButton;
    //outStream << bytesButtonFlag;
    //outStream << pressFlagValue;
    outStream << flagButtonPressed;
    outStream << printButtonList();

    outStream.flush();
    return *outArray;
}

QByteArray Controller::printVectorList()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    int i = 0;
    while(i < vectors.size())
    {
        outStream << "\nList of Vector" << i << "\n";
        outStream << vectors[i].printInfo(i);
        i++;
    }

    outStream.flush();
    return *outArray;
}

QString Controller::findNameForButton(int buttonValue){
    QString name;
    int i = 0;
    while(i < buttons.size()){
        if(buttons[i].getBitMaskPressed()==buttonValue){
            name = buttons[i].getName();
        }
        i++;
    }
    return name;
}
