#include "xmlreader.h"

//Read XML and return Controller
Controller XMLReader::OpenXMLFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                std::cerr << "Error: Cannot read file " << qPrintable(filename)
                          << ": " << qPrintable(file.errorString())
                          << std::endl;
            }

    Rxml.setDevice(&file);
    Rxml.readNext();
    while(!Rxml.atEnd())
    {
        if(Rxml.isStartElement())
        {
            if(Rxml.name() == "CONTROLLER")
            {
                ReadController();
            }
            else
            {
                 Rxml.raiseError(QObject::tr("Not a bookindex file"));
            }
        }
        else
        {
            Rxml.readNext();
        }
    }
    return control;

}

void XMLReader::ReadController()
{
        while(!Rxml.atEnd())
        {
                if(Rxml.isEndElement())
                {
                        Rxml.readNext();
                        break;
                }
                else if(Rxml.isCharacters())
                {
                        Rxml.readNext();
                }
                else if(Rxml.isStartElement())
                {
                        if(Rxml.name() == "Description")
                        {
                            control.setDescription(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Type")
                        {
                            control.setType(ReadTekstElement());
                        }
                        else if(Rxml.name() == "VendorID")
                        {
                            control.setVendorID(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "ProductID")
                        {
                            control.setProductID(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "Protocol")
                        {
                            control.setProtocol(ReadTekstElement());
                        }
                        else if(Rxml.name() == "SampleRate")
                        {
                            control.setSampleRate(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "Number_of_XY")
                        {
                            control.setNumberOfXY(strtol(ReadTekstElement().toStdString().c_str(),NULL,0));
                            Rxml.readNext();
                            int i = 0;
                            while(i<control.getNumberOfXY())
                            {
                                i++;
                                QString name = "XY_";
                                QString text_integer;
                                name += text_integer.setNum(i);
                                if(Rxml.name() == name)
                                {
                                    xy = ReadXY();
                                }
                                Rxml.readNext();
                            }
                        }
                        else if(Rxml.name() == "Format_button")
                        {
                            control.setFormatButtons(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Bytes_button")
                        {
                            control.setBytesButtons(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "General_Mask")
                        {
                            control.setGeneralButtonMask(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "Flag_Button_pressed")
                        {
                            QString temp = ReadTekstElement();
                            if(temp.toLower() == "true"){
                                control.setFlagButtonPressed(true);
                            }
                            else
                            {
                                control.setFlagButtonPressed(false);
                            }
                        }
                        else if(Rxml.name() == "Number_of_Buttons")
                        {
                            control.setNumberOfButtons(ReadTekstElement().toInt());
                            Rxml.readNext();
                            int i = 0;
                            while(i<control.getNumberOfButtons())
                            {
                                i++;
                                QString name = "Button"; // nog aanpassen
                                QString text_integer;
                                name += text_integer.setNum(i);
                                if(Rxml.name() == name)
                                {
                                    button = ReadButton();
                                }
                                Rxml.readNext();
                            }
                        }
                        else if(Rxml.name() == "Number_of_Vectors")
                        {
                            control.setNumberOfVectors(ReadTekstElement().toInt());
                            Rxml.readNext();
                            int i = 0;
                            while(i<control.getNumberOfVectors())
                            {
                                i++;
                                QString name = "XYZ_"; //
                                QString text_integer;
                                name += text_integer.setNum(i);
                                if(Rxml.name() == name)
                                {
                                    v = ReadVector();
                                }
                                Rxml.readNext();
                            }
                        }
                        Rxml.readNext();
                }
                else
                {
                        Rxml.readNext();
                }
        }
}

SensorXY XMLReader::ReadXY()
{
    SensorXY xy;
    while(!Rxml.atEnd())
        {
                if(Rxml.isEndElement())
                {
                        Rxml.readNext();
                        break;
                }
                else if(Rxml.isCharacters())
                {
                        Rxml.readNext();
                }
                else if(Rxml.isStartElement())
                {
                        if(Rxml.name() == "Format_XY")
                        {
                            xy.setFormat(ReadTekstElement());
                        }
                        if(Rxml.name() == "Bytes_XY")
                        {
                            xy.setBytes(ReadTekstElement().toInt());
                        }
                        if(Rxml.name() == "Fixed")
                        {
                            QString temp = ReadTekstElement();
                            if(temp.toLower() == "true"){
                                xy.setBoolFixedValue(true);
                            }
                            else
                            {
                                xy.setBoolFixedValue(false);
                            }
                        }
                        if(Rxml.name() == "Number_of_Buttons")
                        {
                            xy.setNumberOfButtons(ReadTekstElement().toInt());
                        }
                        if(Rxml.name() == "General_Mask_XY")
                        {
                            xy.setGeneralXYMask(ConvertStringToHex(ReadTekstElement()));
                        }

                        else if(Rxml.name() == "UP")
                        {
                            xy.setUp(ConvertStringToHex(ReadTekstElement()));
                                                    }
                        else if(Rxml.name() == "DOWN")
                        {
                            xy.setDown(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "LEFT")
                        {
                            xy.setLeft(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "RIGHT")
                        {
                            xy.setRight(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "UP_LEFT")
                        {
                            xy.setUpLeft(ConvertStringToHex(ReadTekstElement()));;
                        }
                        else if(Rxml.name() == "DOWN_LEFT")
                        {
                            xy.setDownLeft(ConvertStringToHex(ReadTekstElement()));;
                        }
                        else if(Rxml.name() == "UP_RIGHT")
                        {
                            xy.setUpRight(ConvertStringToHex(ReadTekstElement()));;
                        }
                        else if(Rxml.name() == "DOWN_RIGHT")
                        {
                            xy.setDownRight(ConvertStringToHex(ReadTekstElement()));;
                        }
                        else if(Rxml.name() == "X_AXIS")
                        {
                            Axis x = ReadAxis();
                            xy.setXAxis(x);
                        }
                        else if(Rxml.name() == "Y_AXIS")
                        {
                            Axis y = ReadAxis();
                            xy.setYAxis(y);
                        }
                        Rxml.readNext();
                    }
                    else
                    {
                        Rxml.readNext();
                    }
        }

    control.addXY(xy);
    return xy;
}

Button XMLReader::ReadButton()
{
    Button button;
    while(!Rxml.atEnd())
        {
                if(Rxml.isEndElement())
                {
                        Rxml.readNext();
                        break;
                }
                else if(Rxml.isCharacters())
                {
                        Rxml.readNext();
                }
                else if(Rxml.isStartElement())
                {
                        if(Rxml.name() == "Name")
                        {
                            button.setName(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Press")
                        {
                            button.setBitMaskPressed(ConvertStringToHex(ReadTekstElement()));;
                        }
                        else if(Rxml.name() == "Release")
                        {
                            button.setBitMaskRelease(ConvertStringToHex(ReadTekstElement()));;
                        }
                        Rxml.readNext();
                }
                else
                {
                        Rxml.readNext();
                }
        }
    control.addButton(button);
    return button;
}


VectorSensor XMLReader::ReadVector()
{
    VectorSensor vector;
    while(!Rxml.atEnd())
        {
                if(Rxml.isEndElement())
                {
                        Rxml.readNext();
                        break;
                }
                else if(Rxml.isCharacters())
                {
                        Rxml.readNext();
                }
                else if(Rxml.isStartElement())
                {
                        if(Rxml.name() == "Format_XYZ")
                        {
                            vector.setFormatXYZ(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Bytes_XYZ")
                        {
                            vector.setNumberBytesXYZ(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "General_Mask_XYZ")
                        {
                            vector.setMaskXYZ(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "X_AXIS")
                        {
                            Axis x = ReadAxis();
                            vector.setAxisX(x);
                        }
                        else if(Rxml.name() == "Y_AXIS")
                        {
                            Axis y = ReadAxis();
                            vector.setAxisY(y);
                        }
                        else if(Rxml.name() == "Z_AXIS")
                        {
                            Axis z = ReadAxis();
                            vector.setAxisZ(z);
                        }
                        Rxml.readNext();
                }
                else
                {
                        Rxml.readNext();
                }
        }
    control.addVector(vector);
    return vector;
}


Axis XMLReader::ReadAxis()
{
    Axis axis;
    while(!Rxml.atEnd())
        {
                if(Rxml.isEndElement())
                {
                        Rxml.readNext();
                        break;
                }
                else if(Rxml.isCharacters())
                {
                        Rxml.readNext();
                }
                else if(Rxml.isStartElement())
                {
                        if(Rxml.name() == "Format")
                        {
                            axis.setFormat(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Range_Start")
                        {
                            axis.setRangeStart(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "Range_Stop")
                        {
                            axis.setRangeEnd(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "Mask"){
                            axis.setMask(ConvertStringToHex(ReadTekstElement()));
                        }
                        Rxml.readNext();
                }
                else
                {
                        Rxml.readNext();
                }
        }
    return axis;
}



QString XMLReader::ReadTekstElement()
{
    QString tekst;
    while(!Rxml.atEnd())
    {
    if(Rxml.isEndElement())
        {
        Rxml.readNext();
        break;
    }
    else if(Rxml.isStartElement())
    {
        tekst += Rxml.readElementText();
        Rxml.readNext();
        break;
    }
    else if(Rxml.isCharacters())
    {
        Rxml.readNext();
    }
    else
    {
        Rxml.readNext();
    }
}
return tekst;
}


unsigned long long XMLReader::ConvertStringToHex(QString hexVal){
    unsigned long long i = 0;
    if( hexVal.startsWith( "0x" )){
        i = hexVal.mid( 2 ).toULongLong(0 , 16);
    }
    else if( hexVal.startsWith( "0" ) ){
        i = hexVal.mid( 1 ).toULongLong( 0, 8 );
    }
    else{
        i = hexVal.toULongLong();
    }
    return i;
}
