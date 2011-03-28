#include "button.h"

#include <QString>
#include <QTextStream>

Button::Button(QString initialName, int maskPressed, int maskRelease)
{
        name = initialName;
        bitMaskRelease = maskRelease;
        bitMaskPressed = maskPressed;
}



QByteArray Button::printInfo()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "Button name:\t" << name;
    outStream << "\t Bit Mask Press:\t" << QString::number(bitMaskPressed, 16);

    outStream.flush();
    return *outArray;
}
