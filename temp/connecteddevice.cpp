#include "connecteddevice.h"

connectedDevice::connectedDevice()
{
    //ListAllInfo();
}

void connectedDevice::printConnectedDevice(){
    std::cout << "Name:\t" << name.toStdString() << std::endl;
    std::cout << "Type:\t" << type.toStdString() << std::endl;
    std::cout << "VID:\t" << std::hex << vendorID << std::endl;
    std::cout << "PID:\t" << std::hex << productID << std::endl;
    std::cout << "**********************************************" << std::endl;

}

