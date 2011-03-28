#include "xmlreader.h"

//Read XML and return Controller
Controller XMLReader::OpenXMLFile(QString filename)
{
    //qDebug() << "enter XMLReader";
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
                //std::cout << "CONTROLLER \n\n";
                ReadController();
               // control.printAll();
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
    qDebug() << "enter readController";
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
                            //control.setVendorID(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "VendorID")
                        {
                            control.setVendorID(ConvertStringToHex(ReadTekstElement()));
                            //qDebug() << "id" << QString::number(ConvertStringToHex(ReadTekstElement()), 16);
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

//                                SensorXY *tempXY;
//                                tempXY = &xy;

                                QString name = "XY_";
                                QString text_integer;
                                name += text_integer.setNum(i);
                                if(Rxml.name() == name)
                                {
                                    xy = ReadXY();
                                }
                               // control.addXY(xy);
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
                            //std::cout << "Button " << ReadTekstElement().toStdString() << std::endl;
                           // std::cout << std::hex << ConvertStringToHex(ReadTekstElement()) << std::endl;
                           // std::cout << "Button ";
                            control.setGeneralButtonMask(ConvertStringToHex(ReadTekstElement()));
                        }
                        else if(Rxml.name() == "General_Flag_Button_pressed")
                        {
                            QString temp = ReadTekstElement();
                            //temp.toLower();
                            if(temp.toLower() == "true"){
                                control.setGeneralFlagPressed(true);
                            }
                            else
                            {
                                control.setGeneralFlagPressed(false);
                            }

                        }
                        else if(Rxml.name() == "Format_flag")
                        {
                            control.setFormatFlagButton(ReadTekstElement());
                        }
                        else if(Rxml.name() == "Bytes_flag")
                        {
                            control.setBytesButtonFlag(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "Press_flag_value")
                        {
                            control.setPressFlagValue(ReadTekstElement().toInt());
                        }
                        else if(Rxml.name() == "Flag_Button_pressed")
                        {
                            QString temp = ReadTekstElement();
                            //temp.toLower();
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
                                //control.addButton(temp);
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
        //control.printAll();
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
                            //xy.setFormat(ReadTekstElement());
                        }
                        if(Rxml.name() == "Fixed")
                        {
                            QString temp = ReadTekstElement();
                            //temp.toLower();
                            if(temp.toLower() == "true"){
                                xy.setBoolFixedValue(true);
                            }
                            else
                            {
                                xy.setBoolFixedValue(false);
                            }



                            //xy.setFormat(ReadTekstElement());
                        }
                        if(Rxml.name() == "Number_of_Buttons")
                        {
                            xy.setNumberOfButtons(ReadTekstElement().toInt());
                            //xy.setFormat(ReadTekstElement());
                        }
//                        else if(Rxml.name() == "Range_startvalue")
//                        {
//                            xy.setRangeStart(ReadTekstElement().toInt());
//                        }
//                        else if(Rxml.name() == "Range_stopvalue")
//                        {
//                            xy.setRangeStop(ReadTekstElement().toInt());
//                        }
                        if(Rxml.name() == "General_Mask_XY")
                        {
                            //std::cout << "XY ";
                            xy.setGeneralXYMask(ConvertStringToHex(ReadTekstElement()));
                            //std::cout << "XY " << ReadTekstElement().toStdString() << std::endl;
                            //std::cout << std::hex << ConvertStringToHex(ReadTekstElement()) << std::endl;
                            //xy.setFormat(ReadTekstElement());
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

unsigned long int XMLReader::ConvertStringToHex(QString hexVal){
    unsigned long int i = 0;
    //std::cout << "in: " << hexVal.toStdString() << " out: ";
    if ( hexVal.startsWith( "0x" ) ) i = hexVal.mid( 2 ).toULong(0 , 16);
        //.toInt( 0, 16 );
    else if ( hexVal.startsWith( "0" ) ) i = hexVal.mid( 1 ).toULong( 0, 8 );
    else i = hexVal.toULong();
    //std::cout << std::hex << i << std::endl;
    return i;
}
