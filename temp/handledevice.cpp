#include "handledevice.h"
#include "usablecontrollers.h"
#include <Windows.h>

HandleDevice::HandleDevice(MSG *m, long *result, QObject *parent)
    :QThread(parent),  m(m), result(result)
{
}

void HandleDevice::run()
{
    handleWinEvent(m, result);
}

// Handle WinEvent coming from the server-window
void HandleDevice::handleWinEvent(MSG *m, long *result)
{
    LPBYTE lpb;
    UINT dwSize;
    RAWINPUT *raw;
    int msgType = m->message;
    switch (msgType)
    {
    case WM_INPUT:
        {
            GetRawInputData((HRAWINPUT)m->lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

            lpb = (LPBYTE)malloc(sizeof(LPBYTE) * dwSize);
            if (lpb == NULL){
                printf("NULL\n");
            }
            if (GetRawInputData((HRAWINPUT)m->lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize ){
                printf("GetRawInputData doesn't return correct size !\n");
            }
            raw = (RAWINPUT*)lpb;
            qDebug() << "Key";
            switch (raw->header.dwType)
            {
            case RIM_TYPEHID:{
                    handleIt(raw);
                    qDebug() << "Key";
                    break;
                }
            case RIM_TYPEMOUSE:
                {

                    return;
                }
            case RIM_TYPEKEYBOARD:{
                    handleIt(raw);
                    qDebug() << "Key";
                    break;
                }
            }
            break;
        }
        break;
    }
}

void HandleDevice::handleIt(RAWINPUT *raw)
{
    // Find Vid and Pid
    UINT size = 256;
    TCHAR tBuffer[256] = {0};

    if(GetRawInputDeviceInfo(raw->header.hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
    {
        // Error in reading device name
        return;
    }

    int VendorID;
    int ProductID;
    QString myString = QString::fromWCharArray(tBuffer);

    if(myString.contains("HID"))
    {
        int index = myString.toLower().indexOf("vid");
        QString VID = "0000";
        VID[0] = '0';
        VID[1] = 'x';
        VID[2] = myString[index+4];
        VID[3] = myString[index+5];
        VID[4] = myString[index+6];
        VID[5] = myString[index+7];

        VID.toLower();
        VendorID = 0;
        if(VID.startsWith("0x")){
            VendorID = VID.mid(2).toInt(0,16);}
        else{
            VendorID = VID.toInt();}

        index = myString.toLower().indexOf("pid");
        QString PID = "0000";
        PID[0] = '0';
        PID[1] = 'x';
        PID[2] = myString[index+4];
        PID[3] = myString[index+5];
        PID[4] = myString[index+6];
        PID[5] = myString[index+7];

        PID.toLower();
        ProductID = 0;
        if(PID.startsWith("0x")){
            ProductID = PID.mid(2).toInt(0,16);}
        else{
            ProductID = PID.toInt();}
    }

    unsigned long long keyValue;
    unsigned long long value;
    unsigned long long mask3;
    unsigned long long value3;

    switch (raw->header.dwType)
    {
    case RIM_TYPEHID:
        keyValue = *reinterpret_cast<unsigned long long *>(&raw->data.hid.bRawData);
        break;
    case RIM_TYPEMOUSE:
        break;
    case RIM_TYPEKEYBOARD:
        keyValue = raw->data.keyboard.VKey;
        break;
    }
    QString message;
    int i = 0;
    while(i < UsableControllers::getList().size())
    {
        if(UsableControllers::getList()[i].getVendorID() == VendorID && UsableControllers::getList()[i].getProductID() == ProductID)
        {
            QString nrContr;
            nrContr = nrContr.setNum(i);
            message += nrContr;

            int k = 0;
            while(k<UsableControllers::getList()[i].getSensorXYList().size()){
                QString nr;
                nr = nr.setNum(k);
                bool pressed = true;
                switch (raw->header.dwType)
                {
                case RIM_TYPEHID:
                    // value after using bitmask
                    value = keyValue; //UsableControllers::getList()[i].getSensorXYList()[k].getGeneralXYMask() &
                    break;
                case RIM_TYPEMOUSE:
                    break;
                case RIM_TYPEKEYBOARD:
                    value = raw->data.keyboard.VKey;

                    // Check if press or release
                    if(raw->data.keyboard.Flags == 3 || raw->data.keyboard.Flags == 1){
                        pressed = false;
                    }
                    break;
                }
                qDebug() << "Keyboard" << value;
                if(!pressed){
                    return;
                }

                //test if we have axis or buttons
                if(UsableControllers::getList()[i].getSensorXYList()[k].getFixed()){
                    //fixed buttons
                    qDebug() << "fixed";


                    unsigned int up = UsableControllers::getList()[i].getSensorXYList()[k].getUp();
                    unsigned int down = UsableControllers::getList()[i].getSensorXYList()[k].getDown();
                    unsigned int left = UsableControllers::getList()[i].getSensorXYList()[k].getLeft();
                    unsigned int right = UsableControllers::getList()[i].getSensorXYList()[k].getRight();
                    unsigned int upLeft;
                    unsigned int upRight;
                    unsigned int downLeft;
                    unsigned int downRight;

                    mask3 = UsableControllers::getList()[i].getSensorXYList()[k].getGeneralXYMask();
                    qDebug() << mask3;
                    value3 = value & mask3;

                    qDebug() << up << value << value3;
                    qDebug() << down;
                    qDebug() << left;
                    qDebug() << right;

                    if(UsableControllers::getList()[i].getSensorXYList()[k].getNumberOfButtons() == 4 && raw->header.dwType == RIM_TYPEHID)
                    {
                        upLeft = up|left;
                        upRight = up|right;
                        downLeft = down|left;
                        downRight = down|right;
                    }
                    else if(UsableControllers::getList()[i].getSensorXYList()[k].getNumberOfButtons() == 8)
                    {
                        upLeft = UsableControllers::getList()[i].getSensorXYList()[k].getUpLeft();
                        upRight = UsableControllers::getList()[i].getSensorXYList()[k].getUpRight();
                        downLeft = UsableControllers::getList()[i].getSensorXYList()[k].getDownLeft();
                        downRight = UsableControllers::getList()[i].getSensorXYList()[k].getDownRight();
                    }
                    qDebug() << up << value << value3;
                    qDebug() << down;
                    qDebug() << left;
                    qDebug() << right;

                    if(up == value3){message += " Up" + nr;}
                    if(down == value3){message += " Down" + nr;}
                    if(left == value3){message += " Left" + nr;}
                    if(right == value3){message += " Right" + nr;}
                    if(upLeft == value3){message += " Up" + nr + " Left" + nr;}
                    if(upRight == value3){message += " Up" + nr + " Right" + nr;}
                    if(downLeft == value3){message += " Down" + nr + " Left" + nr;}
                    if(downRight == value3){message += " Down" + nr + " Right" + nr;}
                }
                else{
                //XY-axis, because XY was not fixed
                    //X-axis
                    signed long long valueX = UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getMask() & value;
                    qDebug("%x %x %x \n", valueX , value , UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getMask());
                    valueX /= (UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getMask()/0xff);
                    qDebug() << valueX;
                    if(valueX > UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getRangeStop()){
                        valueX -= (UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getRangeStop()-UsableControllers::getList()[i].getSensorXYList()[k].getXAxis().getRangeStart() + 1);
                    }
                    QString valX;
                    valX = valX.setNum(valueX);
                    message += " PX" + nr + "_" + valX;

                    //Y-axis
                    long long valueY = UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getMask() & value;
                    valueY /= (UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getMask()/0xff);
                    if(valueY > UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getRangeStop() && UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getFormat().toLower() == "signed"){
                        valueY -= (UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getRangeStop()-UsableControllers::getList()[i].getSensorXYList()[k].getYAxis().getRangeStart() + 1);
                    }
                    QString valY;
                    valY = valY.setNum(valueY);
                    message += " PY" + nr + "_" + valY;
                }
                k++;
            }

            // Check buttons
            if(raw->header.dwType == RIM_TYPEHID)
            {
                int j = 0;
                int value2 = UsableControllers::getList()[i].getGeneralButtonMask() & keyValue;
                while(j < UsableControllers::getList()[i].getButtonList().size())
                {
                    if(UsableControllers::getList()[i].getButtonList()[j].getBitMaskPressed() & value2 )
                    {
                        message += " " + UsableControllers::getList()[i].getButtonList()[j].getName();
                    }
                    j++;
                }
            }
            else if(raw->header.dwType == RIM_TYPEKEYBOARD)
            {
                int j = 0;
                int value2 = raw->data.keyboard.VKey;
                while(j<UsableControllers::getList()[i].getButtonList().size())
                {
                    if(UsableControllers::getList()[i].getButtonList()[j].getBitMaskPressed() == value2 )
                    {
                        message += " " + UsableControllers::getList()[i].getButtonList()[j].getName();
                    }
                    j++;
                }
            }
        }
        i++;
    }
    if(message != ""){
        qDebug() << message;
        emit buttonAction(message);
    }
}
