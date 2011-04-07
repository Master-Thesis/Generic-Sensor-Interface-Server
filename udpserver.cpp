#include "udpserver.h"

#include <QChar>
#include "mapper.h"
#include "nodesocket.h"

const QList<QString> UDPServer::COMMANDS  =  QList<QString>()
                                             << "help"
                                             << "lsdvs"
                                             << "sldvc"
                                             << "dsdvc"
                                             << "lsbts"
                                             << "kmap"
                                             << "umap"
                                             << "supdvs"
                                             << "afmap"
                                             << "akmap";

UDPServer::UDPServer(bool useLocalHost, QObject *parent) :
    NodeSocket(useLocalHost, parent)
{
    qDebug() << "UDPServer::UDPServer Called";

    //connect(mapper, SIGNAL(actionHappened(QString)), this, SLOT(sendAction(QString)));
    //connect(this, SIGNAL(dataReplyReceived(QString)), this, SLOT(processDataReply(QString)));
}

UDPServer::~UDPServer()
{
    udpSocket->close();

    qDebug() << "Server Object Destroyed";
}

void UDPServer::startSocket()
{
    // Bind to ip and port

    qDebug() << "UDPClient binded, trying to start";

    startServer();
    emit connected(true);
}

void UDPServer::sendControllerAction(const QString action)
{
    qDebug() << "UDPServer::sendControllerAction entered, taking appropriate action";

    QString msg = "20;";
    msg += action;

    // TODO: make reaction dependable on value of action
    // for now just send the action to the client
    sendDatagram(msg.toLatin1());
}


/*
 *
 * PRIVATE SLOTS
 *
 */

void UDPServer::handleDataRequest(QString data)
{
    qDebug() << "UDPServer::handleDataRequest called with data:" << data;
    QString cmd = data.section(';',1,1).toLower();
    switch (COMMANDS.indexOf(cmd.section(' ',0,0)))
    {
    case 0: // Help command (help)
        qDebug() << "help command called";
        sendHelp();
        break;
    case 1: // List devices command (lsdvs)
        qDebug() << "List devices command called";
        sendDeviceList();
        break;
    case 2: // Select device command (sldvc)
        qDebug() << "Select device command called";
        selectDevice(cmd);
        break;
    case 3: // Deselect device command (dsdvc)
        qDebug() << "Deselect device command called";
        deselectDevice();
        break;
    case 4: // List buttons command (lsbts)
        qDebug() << "List buttons command called";
        listButtons();
        break;
    case 5: // Keymap command (kmap)
        qDebug() << "Keymap command called";
        mapKey(cmd);
        break;
    case 6: // Undo keymap command (umap)
        qDebug() << "Undo keymap command called";
        unmapKey(cmd);
        break;
    case 7: // Supported devices command (supdvs)
        qDebug() << "Supported devices command called";
        supportedDevices(cmd);
        break;
    case 8: // Axis Format Map (afmap)
        qDebug() << "Axis Format Map command called";
        axisFormatMap(cmd);
        break;
    case 9: // Axis Key Map (akmap)
        qDebug() << "Axis Key Map command called";
        axisKeyMap(cmd);
        break;
    default:
        qDebug() << "Command not recognised";
        QString reply = "10;";
        reply += "\'" + cmd.section(' ',0,0) + "\'";
        reply += " is not recognized as a command, use the \'help\' command for more information";
        sendDatagram(reply.toLatin1());
        break;
    }

    emit dataAvailable(data);
}

//void UDPServer::sendAction(const QString action)
//{
//    QString msg = "20;";
//    msg += action;
//    sendDatagram(msg.toLatin1());
//}

/*
 *
 * PRIVATE
 *
 */

void UDPServer::sendHelp()
{
    QString hlp = "10;";
    hlp += "\nFor more information on a specific command, type HELP command-name\n";
    hlp += "HELP\tProvides Help information for possible comments\n";
    hlp += "LSDVS\tGenerates a numbered list of all connected devices\n";
    hlp += "SLDVC\tSelects a certain device\n";
    hlp += "DSDVC\tDeselects a certain device\n";
    hlp += "LSBTS\tGenerates a list of all usable buttons on the selected device\n";
    hlp += "KMAP\tBinds button to certain String\n";
    hlp += "UMAP\tUndo a bind of a certain button";
    hlp += "SUPDVS\tGenerates a numberd list of all supported devices (with extra parameters b, p and v if needed)";
    hlp += "AFMAP\tMap a certain format to an axis ((String)axisName (int)ranges (int)start (int)end (bool)inverted)";
    hlp += "AKMAP\tMap an axis to a certain String ((String)axisName (int)range (String)target)";

    sendDatagram(hlp.toLatin1());
}

void UDPServer::sendDeviceList()
{
    QString dvcs = "10;";
    dvcs += QString(UsableControllers::printAllShortList());
    sendDatagram(dvcs.toLatin1());
}

void UDPServer::selectDevice(const QString cmd)
{
    QString msg = "10;";
    int deviceId = cmd.section(' ', 1, 1).toInt();

    if(Mapper::instance()->tryDeviceSelect(deviceId))
        msg += "Device successfully selected!";
    else
        msg += "Error: Device was not selected, please try again";

    sendDatagram(msg.toLatin1());
}

void UDPServer::deselectDevice()
{
    QString msg = "10;";

    if(Mapper::instance()->tryDeviceSelect(-1))
        msg += "Device successfully deselected!";
    else
        msg += "Error: Device was not deselected, please try again";

    sendDatagram(msg.toLatin1());
}

void UDPServer::listButtons()
{
    QString msg = "10;";
    msg += Mapper::instance()->getSelectedController().printAll();
    //msg += "TODO: append button list";
    sendDatagram(msg.toLatin1());
}

void UDPServer::mapKey(const QString cmd)
{
    QString msg = "10;";
    QString source = cmd.section(' ', 1, 1);
    QString target = cmd.section(' ', 2, 2);

    if(Mapper::instance()->tryKeyMap(source, target))
        msg += "Key successfully mapped!";
    else
        msg += "Error: Key was not mapped, please try again";

    sendDatagram(msg.toLatin1());
}

void UDPServer::unmapKey(const QString cmd)
{
    QString msg = "10;";
    QString target = cmd.section(' ', 1, 1);

    if(Mapper::instance()->tryUndoKeyMap(target))
        msg += "Key successfully unmapped!";
    else
        msg += "Error: Key was not unmapped, please try again";

    sendDatagram(msg.toLatin1());
}

void UDPServer::supportedDevices(const QString cmd)
{
    QString msg = "10;";
    QMap<QString, int> map;
    QString cmdStr;
    QString methodString;
    qDebug() << "cmd" << cmd;

    QStringList cmdList;
    cmdList = cmd.split(' ');
    cmdList.removeFirst();

    for(int i = 0; i < cmdList.size(); i++)
    {
        int intPos = cmdList[i].size() - 1;
        int number = cmdList[i].toLower().data()[intPos].digitValue();

        cmdStr = cmdList[i].remove(intPos,1);

        map[cmdStr] =  number;
    }

    methodString.append(QString("b %1,").arg(map.value("b", 0)));
    methodString.append(QString("p %1,").arg(map.value("p", 0)));
    methodString.append(QString("v %1").arg(map.value("v", 0)));

    qDebug() << "methodString: " << methodString;

    msg += SupportedDevices::instance()->printDevicesWithString(methodString);

    sendDatagram(msg.toLatin1());
}

void UDPServer::axisFormatMap(const QString cmd)
{
    // tryAxisFormatMap(const QString axisName, const int ranges, const int start, const int end, const bool inverted)
    QString msg = "10;";

    // Process the cmd String
    QString axisName = cmd.section(' ', 1, 1);
    int ranges = cmd.section(' ', 2, 2).toInt();
    int start = cmd.section(' ', 3, 3).toInt();
    int end = cmd.section(' ', 4, 4).toInt();
    QString invertedString = cmd.section(' ', 5, 5).toLower();

    bool inverted = (invertedString == "inverted");

    if(Mapper::instance()->tryAxisFormatMap(axisName, ranges, start, end, inverted))
        msg += "Axis Format successfully mapped!";
    else
        msg += "Error: Axis Format was not mapped, please try again";

    sendDatagram(msg.toLatin1());
}

void UDPServer::axisKeyMap(const QString cmd)
{
    // tryAxisMapToKey(const QString axisName, const int range, const QString target)
    QString msg = "10;";

    // Process the cmd String
    QString source = cmd.section(' ', 1, 1);
    int range = cmd.section(' ', 2, 2).toInt();
    QString target = cmd.section(' ', 3, 3);

    if(Mapper::instance()->tryAxisMapToKey(source, range, target))
        msg += "Axis successfully mapped to key!";
    else
        msg += "Error: Axis was not mapped to key, please try again";

    sendDatagram(msg.toLatin1());
}

