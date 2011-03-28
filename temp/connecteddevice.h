#ifndef CONNECTEDDEVICE_H
#define CONNECTEDDEVICE_H

#include <QString>
#include <iostream>

class connectedDevice
{
public:
    connectedDevice();

    bool operator==(const connectedDevice & cd);

    //Getters
    QString getName() const {return name;}
    QString getType() const {return type;}
    int getVendorID() const {return vendorID;}
    int getProductID() const {return productID;}

    //Setters
    void setName(QString newName) {name = newName;}
    void setType(QString newType) {type = newType;}
    void setVendorID(int newVendorID){ vendorID = newVendorID;}
    void setProductID(int newProductID){productID = newProductID;}

    void printConnectedDevice();

private:
    QString name;
    QString type;
    int vendorID;
    int productID;

};

#endif // CONNECTEDDEVICE_H
