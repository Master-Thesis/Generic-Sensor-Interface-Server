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
                   int productID,
                   QString protocol,
                   int sampleRate);
        Controller(){}
        ~Controller(){}

        // Getters General Info
        QString getDescription() {return description;}
        long getVendorID() {return vendorID;}
        long getProductID() {return productID;}
        QString getProtocol() {return protocol;}
        int getSampleRate() {return sampleRate;}

        // Setters General Info
        void setDescription(QString newDescription) {description = newDescription;}
        void setType(QString newType) {type = newType;}
        void setVendorID(long newVendorID) {vendorID = newVendorID;}
        void setProductID(long newProductID) {productID = newProductID;}
        void setProtocol(QString newProtocol) {protocol = newProtocol;}
        void setSampleRate(int newSampleRate) {sampleRate = newSampleRate;}

        // Getters Buttons Part
        int getNumberOfBytesButtons() {return numberOfBytesButtons;}
        int getNumberOfButtons() {return numberOfButtons;}
        QList<Button> getButtonList(){ return buttons;}
        QString getFormatButtons() {return formatButtons;}

        // Setters Buttons Part
        void setNumberOfButtons(int newNumberButtons) {numberOfButtons = newNumberButtons;}
        void setFormatButtons(QString newFormatButtons) {formatButtons = newFormatButtons;}
        //void setGeneralFlagPressed(bool newFlag) {generalFlagPressed = newFlag;}
        //void setFormatFlagButton(QString newFormatFlagButton){ formatFlagButton = newFormatFlagButton;}
        //void setBytesButtonFlag(int newBytesButtonFlag) {bytesButtonFlag = newBytesButtonFlag;}
        //void setPressFlagValue(int newPressFlagValue){ pressFlagValue = newPressFlagValue;}
        void setFlagButtonPressed(bool newFlagButtonPressed) {flagButtonPressed = newFlagButtonPressed;} //
        void setBytesButtons(int newBytesButtons) {numberOfBytesButtons = newBytesButtons;}
        void setGeneralButtonMask(unsigned long long newGeneralButtonMask) {generalButtonMask = newGeneralButtonMask;}
        unsigned long long getGeneralButtonMask() {return generalButtonMask;}

        // Setters XYZ Part
        void setNumberOfVectors(int newNumberXYZ){numberOfXYZ = newNumberXYZ;}

        // Getters XYZ Part
        QList<VectorSensor> getVectorList(){ return vectors;}
        int getNumberOfVectors(){return numberOfXYZ;}


        // Getters XY Part
        int getNumberOfXY() {return numberOfXY;}
        QList<SensorXY> getSensorXYList(){return xySensors;}
        void setNumberOfXY(int newNumberXY) {numberOfXY = newNumberXY;}

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
        QString protocol;
        int sampleRate;

        //Info of all the buttons
        int numberOfButtons;
        QList<Button> buttons;
        QString formatButtons;
        int numberOfBytesButtons;
        unsigned long long generalButtonMask;
        //bool generalFlagPressed;
        //QString formatFlagButton;
        //int bytesButtonFlag;
        //int pressFlagValue;
        bool flagButtonPressed;

        //Info of all XY sensors
        int numberOfXY;
        QList<SensorXY> xySensors;
        QString formatXYSensors;
        int numberOfBytesXYSensors;

        //Info of all Vectors, XYZ sensors
        int numberOfXYZ;
        QList<VectorSensor> vectors;





};

#endif // CONTROLLER_H
