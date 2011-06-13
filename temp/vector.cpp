#include "vector.h"
#include <QTextStream>

VectorSensor::VectorSensor()
{
    maskXYZ = 0;
}

QByteArray VectorSensor::printInfo(int nr) const
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    outStream << "\tVX" << nr << "\n";
    outStream << "\tVY" << nr << "\n";
    outStream << "\tVZ" << nr << "\n";

    outStream.flush();
    return *outArray;
}
