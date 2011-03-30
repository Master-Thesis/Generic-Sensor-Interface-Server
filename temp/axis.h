#ifndef AXIS_H
#define AXIS_H
#include <QString>

class Axis
{
public:
    Axis();

    //getters
    QString getFormat(){return format;}
    int getRangeStart(){return rangeStart;}
    int getRangeStop(){return rangeEnd;}
    unsigned long long getMask(){return mask;}

    //setters
    void setFormat(QString newFormat){format = newFormat;}
    void setRangeStart(int newRangeStart){rangeStart = newRangeStart;}
    void setRangeEnd(int newRangeEnd){rangeEnd = newRangeEnd;}
    void setMask(unsigned long long newMask){mask = newMask;}


private:
    QString format;
    int rangeStart;
    int rangeEnd;
    unsigned long long mask;
};

#endif // AXIS_H
