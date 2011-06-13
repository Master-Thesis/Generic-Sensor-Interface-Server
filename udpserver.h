#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QtNetwork>

#include "temp/supporteddevices.h"
#include "mapper.h"
#include "nodesocket.h"

class UDPServer : public NodeSocket
{
    Q_OBJECT

public:
    explicit UDPServer(bool useLocalHost, QObject *parent = 0);
    virtual ~UDPServer();

public slots:
    void startSocket();
    void sendControllerAction(const QString action);

signals:
    void isConnected(bool);
    void dataRequestReceived(QString);
    void dataAvailable(QString);

private slots:
    void handleDataRequest(QString data);

private:
    void sendSYNACK();
    void sendAME();

    void sendHelp();
    void sendDeviceList();
    void selectDevice(const QString cmd);
    void deselectDevice();
    void listButtons();
    void mapKey(const QString cmd);
    void unmapKey(const QString cmd);
    void supportedDevices(const QString cmd);
    void axisFormatMap(const QString cmd);
    void axisKeyMap(const QString cmd);

    void processDatagram(const QByteArray &datagram);

    Mapper *mapper;
    static const QList<QString> COMMANDS;

};

#endif // UDPSERVER_H
