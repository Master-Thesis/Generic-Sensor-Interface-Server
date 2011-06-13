#ifndef BUTTON_H
#define BUTTON_H

#include <QString>
#include <iostream>

class Button
{
public:
        Button(QString initialName, int maskPressed);
        Button(){}
        ~Button(){}

        //getters
        QString getName() {return name;}
        int getBitMaskPressed() {return bitMaskPressed;}

        //setters
        void setName(QString newName) {name = newName;}
        void setBitMaskPressed(long int newMaskPressed) {bitMaskPressed = newMaskPressed;}

        //print
        QByteArray printInfo();

private:
        QString name;
        long int bitMaskPressed;
};

#endif // BUTTON_H
