#ifndef AXISOUTMAPPER_H
#define AXISOUTMAPPER_H

#include <QChar>
#include <QString>

class AxisOutMapper
{
public:
    AxisOutMapper(){}
    ~AxisOutMapper(){}

    // Getters
    int getControllerNr(){return controllerNr;}
    QChar getAxis(){return axis;}
    int getXYnr(){return xyNr;}
    int getRangeNr(){return range;}
    QString getAction(){return action;}
    QChar getType(){return type;}

    // Setters
    void setControllerNr(int newControllerNr){controllerNr = newControllerNr;}
    void setAxis(QChar newAxis){axis = newAxis;}
    void setType(QChar newType){type = newType;}
    void setXYnr(int newXY){xyNr = newXY;}
    void setRangeNr(int newNr){range = newNr;}
    void setAction(QString newAction){action = newAction;}

private:
    int controllerNr;
    QChar axis;
    int xyNr;
    int range;
    QString action;
    QChar type;
};

#endif // AXISOUTMAPPER_H
