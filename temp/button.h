#ifndef BUTTON_H
#define BUTTON_H

#include <QString>
#include <iostream>

class Button
{
public:
        Button(QString initialName, int maskPressed, int maskRelease);
        Button(){}
        ~Button(){}

        //getters
        QString getName() {return name;}
        int getBitMaskPressed() {return bitMaskPressed;}
        int getBitMaskRelease() {return bitMaskRelease;}
        QByteArray printInfo();

        //setters
        void setName(QString newName) {name = newName;}
        void setBitMaskPressed(long int newMaskPressed) {bitMaskPressed = newMaskPressed;}
        void setBitMaskRelease(long int newMaskRelease) {bitMaskRelease = newMaskRelease;}

private:
        QString name;
        long int bitMaskPressed;
        long int bitMaskRelease;
};

#endif // BUTTON_H
