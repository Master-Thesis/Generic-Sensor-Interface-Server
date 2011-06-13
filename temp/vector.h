#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <QDebug>
#include <QString>
#include "axis.h"

class VectorSensor
{
public:
    VectorSensor();
    ~VectorSensor(){}

    //setters
    void setFormatXYZ(QString newFormat){formatXYZ = newFormat;}
    void setNumberBytesXYZ(int newNumberBytesXYZ){numberBytesXYZ = newNumberBytesXYZ;}
    void setMaskXYZ(unsigned long long newMaskXYZ){maskXYZ = newMaskXYZ;}
    void setAxisX(Axis newX){x = newX;}
    void setAxisY(Axis newY){y = newY;}
    void setAxisZ(Axis newZ){z = newZ;}

    //getters
    Axis getAxisX(){return x;}
    Axis getAxisY(){return y;}
    Axis getAxisZ(){return z;}
    unsigned long long getGeneralMaskXYZ(){return maskXYZ;}

    //printing
    QByteArray printInfo(int nr) const;

private:
    QString formatXYZ;
    int numberBytesXYZ;
    unsigned long long maskXYZ;
    Axis x;
    Axis y;
    Axis z;


};

#endif // VECTOR_H
