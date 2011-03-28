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
            switch (raw->header.dwType)
            {
            case RIM_TYPEHID:{
                    handleIt(raw);
                    break;
                }
            case RIM_TYPEMOUSE:
                {
                    break;
                }
            case RIM_TYPEKEYBOARD:{
                    handleIt(raw);
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
    }

    int VendorID;
    int ProductID;
    QString myString = QString::fromWCharArray(tBuffer);

    if(myString.contains("HID"))
    {
        int index = myString.indexOf("VID");
        QString VID = "0000";
        VID[0] = '0';
        VID[1] = 'x';
        VID[2] = myString[index+4];
        VID[3] = myString[index+5];
        VID[4] = myString[index+6];
        VID[5] = myString[index+7];

        VID.toLower();
        int i = 0;
        if ( VID.startsWith( "0x" ) ) i = VID.mid( 2 ).toInt( 0, 16 );
        else if ( VID.startsWith( "0" ) ) i = VID.mid( 1 ).toInt( 0, 8 );
        else i = VID.toInt();
        VendorID = i;

        index = myString.indexOf("PID");
        QString PID = "0000";
        PID[0] = '0';
        PID[1] = 'x';
        PID[2] = myString[index+4];
        PID[3] = myString[index+5];
        PID[4] = myString[index+6];
        PID[5] = myString[index+7];

        PID.toLower();
        i = 0;
        if ( PID.startsWith( "0x" ) ) i = PID.mid( 2 ).toInt( 0, 16 );
        else if ( PID.startsWith( "0" ) ) i = PID.mid( 1 ).toInt( 0, 8 );
        else i = PID.toInt();
        ProductID = i;
    }

    unsigned long int dwKeystate;
    unsigned long waarde;

    switch (raw->header.dwType)
    {
    case RIM_TYPEHID:
        dwKeystate = *reinterpret_cast<unsigned long *>(&raw->data.hid.bRawData);
        break;
    case RIM_TYPEMOUSE:
        break;
    case RIM_TYPEKEYBOARD:
        dwKeystate = raw->data.keyboard.VKey;
        break;
    }

    int size2 = UsableControllers::getList().size();
    int i = 0;
    QString message;

    while(i < size2)
    {
        if(UsableControllers::getList()[i].getVendorID() == VendorID && UsableControllers::getList()[i].getProductID() == ProductID)
        {
           // message += UsableControllers::getList()[i].getDescription() + "\t";
            QString nrContr;
            nrContr = nrContr.setNum(i);
            message += nrContr;
            int k = 0;
            QString nr;
            nr = nr.setNum(k);

            switch (raw->header.dwType)
            {
            case RIM_TYPEHID:
                    waarde = UsableControllers::getList()[i].getSensorXYList()[k].getGeneralXYMask() & dwKeystate; //voor thrustmaster
                    break;
            case RIM_TYPEMOUSE:
                    break;
            case RIM_TYPEKEYBOARD:
                    waarde = raw->data.keyboard.VKey;
                    break;
            }

            unsigned int up = UsableControllers::getList()[i].getSensorXYList()[k].getUp();
            unsigned int down = UsableControllers::getList()[i].getSensorXYList()[k].getDown();
            unsigned int left = UsableControllers::getList()[i].getSensorXYList()[k].getLeft();
            unsigned int right = UsableControllers::getList()[i].getSensorXYList()[k].getRight();
            unsigned int upLeft;
            unsigned int upRight;
            unsigned int downLeft;
            unsigned int downRight;

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

            if(up == waarde){message += " Up" + nr;}
            if(down == waarde){message += " Down" + nr;}
            if(left == waarde){message += " Left" + nr;}
            if(right == waarde){message += " Right" + nr;}
            if(upLeft == waarde){message += " Up" + nr + " Left" + nr;}
            if(upRight == waarde){message += " Up" + nr + " Right" + nr;}
            if(downLeft == waarde){message += " Dow" + nr + " Left" + nr;}
            if(downRight == waarde){message += " Down" + nr + " Right" + nr;}

            if(raw->header.dwType == RIM_TYPEHID)
            {
                int j = 0;
                int waarde2 = UsableControllers::getList()[i].getGeneralButtonMask() & dwKeystate; //Thrustmaster
                while(j < UsableControllers::getList()[i].getButtonList().size())
                {
                    if(UsableControllers::getList()[i].getButtonList()[j].getBitMaskPressed() & waarde2 )
                    {
                        message += " " + UsableControllers::getList()[i].getButtonList()[j].getName();
                    }
                    j++;
                }
            }
            else if(raw->header.dwType == RIM_TYPEKEYBOARD)
            {
                int j = 0;
                int waarde2 = raw->data.keyboard.VKey; //Thrustmaster
                while(j<UsableControllers::getList()[i].getButtonList().size())
                {
                    if(UsableControllers::getList()[i].getButtonList()[j].getBitMaskPressed() == waarde2 )
                    {
                        message += " " + UsableControllers::getList()[i].getButtonList()[j].getName();
                    }
                    j++;
                }
            }
        }
        i++;
    }

    qDebug() << message;
    emit buttonAction(message);
}
