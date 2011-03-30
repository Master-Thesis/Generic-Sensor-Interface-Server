#ifndef VECTOR_H
#define VECTOR_H

#include <QString>
#include "axis.h"

class Vector
{
public:
    Vector();

    //setters
    void setFormatXYZ(QString newFormat){formatXYZ = newFormat;}
    void setNumberBytesXYZ(int newNumberBytesXYZ){numberBytesXYZ = newNumberBytesXYZ;}
    void setMaskXYZ(unsigned long long newMaskXYZ){maskXYZ = newMaskXYZ;}
    void setAxisX(Axis newX){x = newX;}
    void setAxisY(Axis newY){y = newY;}
    void setAxisZ(Axis newZ){z = newZ;}

    //getters
    Axis getAxisX(){return x;}

private:
    //int numberOfXYZ;
    QString formatXYZ;
    int numberBytesXYZ;
    unsigned long long maskXYZ;
    Axis x;
    Axis y;
    Axis z;


};

#endif // VECTOR_H
