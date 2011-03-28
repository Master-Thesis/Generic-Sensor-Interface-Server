#include "mapper.h"

#include "temp/button.h"
#include "temp/usablecontrollers.h"

#include <QStringList>
#include <QMutex>

static QMutex mutex;

Mapper* Mapper::m_mapper = 0;
int Mapper::controllerNo;
QList<QString> Mapper::buttonList;
QList<QString> Mapper::mappingList;

Mapper::Mapper(QObject *parent) :
    QObject(parent)
{
    controllerNo = -1;

    //controllers = new ConnectedSupportedControllers;

    // TODO: Delete
    //devices.reserve(10);
    //devices = controllers->getAllConnectedSupportedList();
}

Mapper::~Mapper()
{
}

Mapper* Mapper::instance()
{
    if(!m_mapper)
    {
        mutex.lock();

        if(!m_mapper)
            m_mapper = new Mapper();

        mutex.unlock();
    }

    return m_mapper;
}

void Mapper::drop()
{
    mutex.lock();
    delete m_mapper;
    m_mapper = 0;
    mutex.unlock();
}

Controller Mapper::getSelectedController()
{
    return UsableControllers::getList().at(controllerNo);
}

// function to select a certain controller
// to deselect call this function with deviceNo = -1
bool Mapper::tryDeviceSelect(const int deviceNo)
{
    bool status = false;

    if(UsableControllers::getList().isEmpty() || deviceNo >= UsableControllers::getList().size())
        return status;

    controllerNo = deviceNo;
    status = true;

    // TODO: Uncomment and implement
    if(deviceNo == -1)
    {
        while(!buttonList.isEmpty())
            buttonList.pop_back();

        return status;
    }

    int buttonSize = UsableControllers::getList()[controllerNo].getButtonList().size();
    for(int i = 0; i <  buttonSize; i++)
        buttonList << UsableControllers::getList()[controllerNo].getButtonList()[i].getName().toLower();

    int xySize = UsableControllers::getList()[controllerNo].getNumberOfXY();
    for(int i = 0; i < xySize; i++)
        buttonList << ("up" + QString::number(i)) << ("down" + QString::number(i)) << ("left" + QString::number(i)) << ("right" + QString::number(i));

    //buttonList.reserve(buttonSize + (xySize * 4));
    Mapper::instance()->initQStringList(mappingList, buttonList.size());

    return status;
}

//bool Mapper::tryDeviceDeselect(const int newDevice)
//{
//    bool status = false;

//    // if no device is selected
//    status = tryDeviceSelect(newDevice);

//    return status;
//}

bool Mapper::tryKeyMap(const QString source, const QString target)
{
    bool status = false;

    // if no controller selected or the buttonlist is not filled -> return
    if (controllerNo == -1 || buttonList.isEmpty())
        return status;

    // if the source key is allready binded or the target key is allready binded -> return
    int index = buttonList.indexOf(source.toLower());
    if (mappingList.contains(target.toLower()) || !mappingList.value(index).isEmpty())
        return status;

    // otherwise bind the key
    mappingList.replace(index, target.toLower());
    status = true;

    return status;
}

bool Mapper::tryUndoKeyMap(const QString target)
{
    bool status = false;

    if(!mappingList.contains(target))
        return status;

    mappingList.replace(mappingList.lastIndexOf(target), "");

    return status;
}

// Slot that responds to actions manifested
// If the action has a binded button the signal is emitted
void Mapper::checkActions(const QString actions)
{
    qDebug() << "Mapper::checkActions, actions: " << actions;
    QString action;
    QStringList actionList;
    actionList = actions.split(' ');
    int deviceId = actionList[0].toInt();
    actionList.removeFirst();

    if(controllerNo != deviceId || actionList.isEmpty())
        return;

    for(int i = 0; i < actionList.size(); i++)
    {
        QString buttonName = actionList[i].toLower();

        qDebug() << "Mapper::checkActions, buttonName: " << buttonName;

        if(buttonList.contains(buttonName))
        {
            action = mappingList.at(buttonList.indexOf(buttonName));
            emit actionHappened(action);
            qDebug() << "Mapper: button action emitted";
        }
    }
}

void Mapper::initQStringList(QList<QString> &list, const int size)
{
    //list.reserve(size);

    while(!list.isEmpty())
        list.removeLast();

    for(int i = 0; i < size; i++)
    {
        list.append("");
    }
}


