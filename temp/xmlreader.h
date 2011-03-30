#ifndef XMLREADER_H
#define XMLREADER_H

#include <QString>
#include "controller.h"
#include <QXmlStreamReader>
#include <iostream>
#include <QFile>
#include "vector.h"

class XMLReader
{
public:
    XMLReader(){}
    ~XMLReader(){}
    Controller OpenXMLFile(QString);
    void ReadController();
    QString ReadTekstElement();
    SensorXY ReadXY();
    Button ReadButton();
    unsigned long long ConvertStringToHex(QString hexVal);
    Axis ReadAxis();
    Vector ReadVector();

private:
    Controller control;
    SensorXY xy;
    Button button;
    Vector v;
    QXmlStreamReader Rxml;
    QString filename;

};

#endif // XMLREADER_H
