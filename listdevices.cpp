#include "listdevices.h"
#if (_WIN32_WINNT < 0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QTextStream>

using namespace std;


ListDevices::ListDevices()
{
}

QByteArray ListDevices::ListAllInfo()
{
    QByteArray *outArray = new QByteArray();
    QTextStream outStream(outArray);

    UINT nDevices;
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
    {
        outStream << "Errors...\n";
        //return 1;
    }

    if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
    {
        outStream << "Initialization failed...\n";
        //return 1;
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
        UINT size = 256;
        TCHAR tBuffer[256] = {0};

        if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) < 0)
        {
            // Error in reading device name
        }

        // cout << "Device Name: " << tBuffer;
                     printf("Device Name: ");
                     wprintf(tBuffer);
                     printf("\n");
        // _tprintf(L"Device Name: %s\n", tBuffer);

        UINT cbSize = rdi.cbSize;
        if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) < 0)
        {
            // Error in reading information
        }

        if(rdi.dwType == RIM_TYPEMOUSE)
        {
            outStream << "ID for Mouse:" << (quint32) rdi.mouse.dwId << "\n";
            outStream << "Number of Buttons:" << (quint32) rdi.mouse.dwNumberOfButtons << "\n";
            outStream << "Sample rate(Number of data points):" << (quint32) rdi.mouse.dwSampleRate << "\n";
            outStream << "**************************\n";
        }

        if(rdi.dwType == RIM_TYPEKEYBOARD)
        {
            outStream << "Keyboard Mode:" << (quint32) rdi.keyboard.dwKeyboardMode << "\n";
            outStream << "Number of function keys:" << (quint32) rdi.keyboard.dwNumberOfFunctionKeys << "\n";
            outStream << "Number of indicators:" << (quint32) rdi.keyboard.dwNumberOfIndicators << "\n";
            outStream << "Number of keys total: " << (quint32) rdi.keyboard.dwNumberOfKeysTotal << "\n";
            outStream << "Type of the keyboard: " << (quint32) rdi.keyboard.dwType << "\n";
            outStream << "Subtype of the keyboard: " << (quint32) rdi.keyboard.dwSubType << "\n";
            outStream << "***********************\n";
        }

        if(rdi.dwType == RIM_TYPEHID)
        {
            outStream << "Vendor Id:" << (quint32) rdi.hid.dwVendorId << "\n";
            outStream << "Product Id:" << (quint32) rdi.hid.dwProductId << "\n";
            outStream << "Version No:" << (quint32) rdi.hid.dwVersionNumber << "\n";
            outStream << "Usage for the device: " << (quint16) rdi.hid.usUsage << "\n";
            outStream << "Usage Page for the device: " << (quint16) rdi.hid.usUsagePage << "\n";
            outStream << "***********************\n";
        }
    }
    outStream.flush();
    free(pRawInputDeviceList);


    return *outArray;

}
