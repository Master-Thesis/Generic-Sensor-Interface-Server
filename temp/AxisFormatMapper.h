#ifndef AXISFORMATMAPPER_H
#define AXISFORMATMAPPER_H

#include <QString>


// Class to Map the wanted changes to the output value of an axis
class AxisFormatMapper
{
public:
    AxisFormatMapper(){}

    // Getters
    int getControllerNr(){return controllerNr;}
    QString getAxisName(){return axisName;}
    int getNumberOfRanges(){return numberOfRanges;}
    float getLastValue(){return lastValue;}
    int getRangeStart(){return rangeStart;}
    int getRangeEnd(){return rangeEnd;}
    int getLastRange(){return lastRange;}
    bool isInverted(){return inverted;}

    // Setters
    void setControllerNr(int newControllerNr){controllerNr = newControllerNr;}
    void setAxisName(QString newAxisName){axisName = newAxisName;}
    void setNumberOfRanges(int newNumberOfRanges){numberOfRanges = newNumberOfRanges;}
    void setLastValue(float newLastValue){lastValue = newLastValue;}
    void setRangeStart(int newRangeStart){rangeStart = newRangeStart;}
    void setRangeEnd(int newRangeEnd){rangeEnd = newRangeEnd;}
    void setLastRange(int newRange){lastRange = newRange;}
    void setInverted(bool newInv){inverted = newInv;}

private:
    int controllerNr;
    QString axisName;
    int numberOfRanges;
    float lastValue;
    int lastRange;
    bool inverted;

    int rangeStart;
    int rangeEnd;
};

#endif // AXISFORMATMAPPER_H
