#ifndef SENSORXY_H
#define SENSORXY_H

#include <QString>
#include <iostream>
#include <QDebug>
#include "axis.h"

class SensorXY
{
public:
    SensorXY();
    ~SensorXY(){}

    QString getFormat() {return format;}
    //int getRangeStart() {return startRange;}
    //int getRangeStop() {return stopRange;}

    void setFormat(QString newFormat) {format = newFormat;}
    //void setRangeStart(int newStart) {startRange = newStart;}
    //void setRangeStop(int newStop) {stopRange = newStop;}
    void setUp(int newUp) {up = newUp;}
    void setDown(int newDown) {down = newDown;}
    void setLeft(int newLeft) {left = newLeft;}
    void setRight(int newRight) {right = newRight;}
    void setBytes(int newBytes) {bytes = newBytes;}
    void setBoolFixedValue(int newFixed) {fixedValue = newFixed;}
    void setNumberOfButtons(int newNumberOfButtons) {numberOfButtons = newNumberOfButtons;}
    void setUpLeft(int newUpLeft) {upLeft = newUpLeft;}
    void setDownLeft(int newDownLeft) {downLeft = newDownLeft;}
    void setUpRight(int newUpRight) {upRight = newUpRight;}
    void setDownRight(int newDownRight) {downRight = newDownRight;}
    void setNumberOfAxis(int newNumberOfAxis) {axis = newNumberOfAxis;}
    void setGeneralXYMask(unsigned long long newGeneralXYMask) {generalXYMask = newGeneralXYMask;}

    void setXAxis(Axis newX){x = newX;}
    void setYAxis(Axis newY){y = newY;}

    Axis getXAxis(){return x;}
    Axis getYAxis(){return y;}

    const int getUp() {return up;}
    const int getDown() {return down;}
    const int getLeft() {return left;}
    const int getRight() {return right;}
    const int getNumberOfButtons() {return numberOfButtons;}

    const int getUpLeft() {return upLeft;}
    const int getDownLeft() {return downLeft;}
    const int getUpRight() {return upRight;}
    const int getDownRight() {return downRight;}
    const unsigned long long getGeneralXYMask() {return generalXYMask;}
    const bool getFixed() {return fixedValue;}

    QByteArray printInfo(int nr) const;
    QByteArray printInfoDetails() const;

private:
    QString format;
    int bytes;
    int up;
    int down;
    int left;
    int right;
    bool fixedValue;
    int numberOfButtons;
    int upLeft;
    int downLeft;
    int upRight;
    int downRight;
    int axis;
    Axis x;
    Axis y;
    unsigned long long generalXYMask;

};

#endif // SENSORXY_H
