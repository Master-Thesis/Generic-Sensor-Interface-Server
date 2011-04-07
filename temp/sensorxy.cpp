#include "sensorxy.h"

SensorXY::SensorXY()
{
}

QByteArray SensorXY::printInfoDetails() const
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    if(numberOfButtons == 4){
        outStream << "Up\t" << QString::number(up, 16);
        outStream << "Down\t" << QString::number(down, 16);
        outStream << "Left\t" << QString::number(left, 16);
        outStream << "Right\t" << QString::number(right, 16);
    }
    else if(numberOfButtons == 8){
        outStream << "Up\t" << QString::number(up, 16);
        outStream << "Down\t" <<  QString::number(down, 16);
        outStream << "Left\t" <<  QString::number(left, 16);
        outStream << "Right\t" <<  QString::number(right, 16);
        outStream << "\nUp Left\t" << QString::number(upLeft, 16);
        outStream << "Down Left\t" <<  QString::number(downLeft, 16);
        outStream << "Up Right\t" <<  QString::number(upRight, 16);
        outStream << "Down Right\t" <<  QString::number(downRight, 16);
    }

    outStream.flush();
    return *outArray;
}

QByteArray SensorXY::printInfo(int nr) const
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    //if(numberOfButtons == 4){
    if(fixedValue){
        outStream << "\tUp" << nr << "\n";
        outStream << "\tDown" << nr << "\n";
        outStream << "\tLeft" << nr << "\n";
        outStream << "\tRight" << nr << "\n";
    }
    else{
        outStream << "\tPX" << nr << "\n";
        outStream << "\tPY" << nr << "\n";
    }
//    else if(numberOfButtons == 8){
//        outStream << "Up\n";
//        outStream << "Down\n";
//        outStream << "Left\n";
//        outStream << "Right\n";
//        outStream << "\nUp Left\n";
//        outStream << "Down Left\n";
//        outStream << "Up Right\n";
//        outStream << "Down Right\n";
//    }

    outStream.flush();
    return *outArray;
}
