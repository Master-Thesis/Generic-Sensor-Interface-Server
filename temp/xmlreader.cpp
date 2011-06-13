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
            else if(Rxml.name().toString().contains("XY_"))
            {
                bool nextXY = true;
                while(nextXY){
                    QString name = "XY_";
                    if(Rxml.name().toString().contains(name))
                    {
                        xy = ReadXY();
                        Rxml.readNext();
                    }
                    else                {
                        nextXY = false;
                    }
                }
            }
            // Read each button
            else if(Rxml.name().toString().contains("Button_"))
            {
                bool nextButton = true;
                while(nextButton){
                    QString name = "Button_"; // nog aanpassen
                    if(Rxml.name().toString().contains(name))
                    {
                        button = ReadButton();
                        Rxml.readNext();
                    }
                    else{
                        nextButton = false;
                    }
                }
            }
            // Read each vector
            else if(Rxml.name().toString().contains("XYZ_"))
            {
                bool nextVector = true;
                while(nextVector){
                    QString name = "XYZ_";
                    if(Rxml.name().toString().contains(name))
                    {
                        v = ReadVector();
                        Rxml.readNext();
                    }
                    else{
                        nextVector = false;
                    }
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
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setUp(maskRead);
            }
            else if(Rxml.name() == "DOWN")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setDown(maskRead);
            }
            else if(Rxml.name() == "LEFT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setLeft(maskRead);
            }
            else if(Rxml.name() == "RIGHT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setRight(maskRead);
            }
            else if(Rxml.name() == "UP_LEFT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setUpLeft(maskRead);
            }
            else if(Rxml.name() == "DOWN_LEFT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setDownLeft(maskRead);
            }
            else if(Rxml.name() == "UP_RIGHT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setUpRight(maskRead);
            }
            else if(Rxml.name() == "DOWN_RIGHT")
            {
                unsigned long long mask = xy.getGeneralXYMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                xy.setGeneralXYMask(mask);
                xy.setDownRight(maskRead);
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
                unsigned long long mask = control.getGeneralButtonMask();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                control.setGeneralButtonMask(mask);

                button.setBitMaskPressed(maskRead);
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

//            else if(Rxml.name() == "General_Mask_XYZ")
//            {






//                vector.setMaskXYZ(ConvertStringToHex(ReadTekstElement()));
//            }
            if(Rxml.name() == "X_AXIS")
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
                unsigned long long mask = v.getGeneralMaskXYZ();
                unsigned long long maskRead = ConvertStringToHex(ReadTekstElement());
                mask |= maskRead;
                v.setMaskXYZ(mask);
                axis.setMask(maskRead);
                //axis.setMask(ConvertStringToHex(ReadTekstElement()));
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
    else{
        i = hexVal.toULongLong();
    }
    return i;
}
