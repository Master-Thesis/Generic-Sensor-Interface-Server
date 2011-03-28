#include "allconnected.h"

AllConnected::AllConnected()
{
    qDebug() << "AllConnected::AllConnected() entered";
    ListAllInfo();
    qDebug() << "Size of the connected List: " << connected.size();
}

void AllConnected::ListAllInfo()
{
    UINT nDevices;
          PRAWINPUTDEVICELIST pRawInputDeviceList;
          if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
          {
              qDebug() << "Errors...";
           }

          if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
          {
             qDebug() << "Initialization failed...";
          }

          int nNoOfDevices = 0;
          if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) == ((UINT) - 1))
          {
             // Error
            // return 1;
          }

          RID_DEVICE_INFO rdi;
          rdi.cbSize = sizeof(RID_DEVICE_INFO);

          for(int i = 0; i < nNoOfDevices; i++)
          {
             connectedDevice newDevice;
             UINT size = 256;
             TCHAR tBuffer[256] = {0};

             if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
             {
                // Error in reading device name
             }
             QString myString = QString::fromWCharArray(tBuffer);
             if(myString.contains("HID")){
                 //printf("Device Name: ");
                 //wprintf(tBuffer);
                // printf("\n");
                 //printf("JEP\n\n\n");
                 int index = myString.indexOf("VID");
                 QString VID = "0x0000";
                 VID[0] = '0';
                 VID[1] = 'x';
                 VID[2] = myString[index+4];
                 VID[3] = myString[index+5];
                 VID[4] = myString[index+6];
                 VID[5] = myString[index+7];
                 //std::cout << "Vendor Id: " << VID.toStdString() << std::endl;
                int vid = ConvertStringToHex(VID);

                 index = myString.indexOf("PID");
                 QString PID = "0x0000";
                 PID[0] = '0';
                 PID[1] = 'x';
                 PID[2] = myString[index+4];
                 PID[3] = myString[index+5];
                 PID[4] = myString[index+6];
                 PID[5] = myString[index+7];
                 //std::cout << "Product Id: " << PID.toStdString() << std::endl;

                 int pid = ConvertStringToHex(PID);

//                 qDebug() << "---------";
//                 qDebug() << "Vendor ID: " << vid;
//                 qDebug() << "Product ID: " << pid;
//                 qDebug() << "---------";



//                 newDevice.setName(all.findNameWithVidPid(vid, pid));
                newDevice.setVendorID(vid);
                newDevice.setProductID(pid);

                 UINT cbSize = rdi.cbSize;
                 if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0)
                 {
                    // Error in reading information
                 }

                 if(rdi.dwType == RIM_TYPEMOUSE)
                 {
                     newDevice.setType("MOUSE");
                 }

                 if(rdi.dwType == RIM_TYPEKEYBOARD)
                 {
                     newDevice.setType("KEYBOARD");
                 }

                 if(rdi.dwType == RIM_TYPEHID)
                 {
                     newDevice.setType("HID");
                 }
                 connected.append(newDevice);
                // std::cout << "added" << std::endl;

             }
}

          free(pRawInputDeviceList);

      }

unsigned long int AllConnected::ConvertStringToHex(QString hexVal){
    unsigned long int i = 0;
    //std::cout << "in: " << hexVal.toStdString() << " out: ";
    if ( hexVal.startsWith( "0x" ) ) i = hexVal.mid( 2 ).toULong(0 , 16);
        //.toInt( 0, 16 );
    else if ( hexVal.startsWith( "0" ) ) i = hexVal.mid( 1 ).toULong( 0, 8 );
    else i = hexVal.toULong();
    //std::cout << std::hex << i << std::endl;
    return i;
}

