#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QList>
#include "button.h"
#include "sensorxy.h"
#include <iostream>
#include <QDebug>
#include "vector.h"

class Controller
{
public:
        Controller(QString description,
                   int vendorID,
                   int productID);
        Controller(){generalButtonMask = 0;}
        ~Controller(){}

        // Getters General Info
        QString getDescription() {return description;}
        long getVendorID() {return vendorID;}
        long getProductID() {return productID;}

        // Setters General Info
        void setDescription(QString newDescription) {description = newDescription;}
        void setType(QString newType) {type = newType;}
        void setVendorID(long newVendorID) {vendorID = newVendorID;}
        void setProductID(long newProductID) {productID = newProductID;}

        // Getters Buttons Part
        int getNumberOfBytesButtons() {return numberOfBytesButtons;}
        QList<Button> getButtonList(){ return buttons;}
        QString getFormatButtons() {return formatButtons;}

        // Setters Buttons Part
        void setFormatButtons(QString newFormatButtons) {formatButtons = newFormatButtons;}
        void setFlagButtonPressed(bool newFlagButtonPressed) {flagButtonPressed = newFlagButtonPressed;} //
        void setBytesButtons(int newBytesButtons) {numberOfBytesButtons = newBytesButtons;}
        void setGeneralButtonMask(unsigned long long newGeneralButtonMask) {generalButtonMask = newGeneralButtonMask;}
        unsigned long long getGeneralButtonMask() {return generalButtonMask;}

        // Getters XYZ Part
        QList<VectorSensor> getVectorList(){ return vectors;}

        // Getters XY Part
        QList<SensorXY> getSensorXYList(){return xySensors;}

        // Print Functions
        QByteArray printAllDetails();
        QByteArray printAll();
        QByteArray printXYList();
        QByteArray printButtonInfo();
        QByteArray printButtonList();
        QByteArray printButtonListDetails();
        QByteArray printVectorList();

        // Other Functions
        void addButton(Button);
        QString findNameForButton(int buttonValue);
        void addXY(SensorXY);
        void addVector(VectorSensor newVector);


private:
        //general information of the controller
        QString description;
        QString type;
        long vendorID;
        long productID;

        //Info of all the buttons
        QList<Button> buttons;
        QString formatButtons;
        int numberOfBytesButtons;
        unsigned long long generalButtonMask;
        bool flagButtonPressed;

        //Info of all XY sensors
        QList<SensorXY> xySensors;
        QString formatXYSensors;
        int numberOfBytesXYSensors;

        //Info of all Vectors, XYZ sensors
        int numberOfXYZ;
        QList<VectorSensor> vectors;


};

#endif // CONTROLLER_H
