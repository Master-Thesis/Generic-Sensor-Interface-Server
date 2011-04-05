#include "mapper.h"

#include "temp/button.h"
#include "temp/usablecontrollers.h"
#include "temp/AxisFormatMapper.h"

#include <QStringList>
#include <QMutex>
#include <QChar>

static QMutex mutex;

Mapper* Mapper::m_mapper = 0;
int Mapper::controllerNo;
QList<QString> Mapper::buttonList;
QList<QString> Mapper::mappingList;

QList<AxisFormatMapper> Mapper::axisFormatMapList; //To Map Changes in output format
QList<AxisOutMapper> Mapper::axisOutMappingList; //To Map a Range to a specific key



Mapper::Mapper(QObject *parent) :
    QObject(parent)
{
    controllerNo = -1;

    //om te testen
    AxisFormatMapper a;
    a.setAxisName("vx0");
    a.setNumberOfRanges(7);
    a.setRangeStart(0);
    a.setRangeEnd(255);
    a.setInverted(false);
    axisFormatMapList.append(a);

    AxisFormatMapper b;
    b.setAxisName("px2");
    b.setNumberOfRanges(1);
    b.setRangeStart(0);
    b.setRangeEnd(100);
    b.setInverted(false);
    axisFormatMapList.append(b);

    AxisOutMapper m;
    m.setAction("tetrixleft");
    m.setAxis('x');
    m.setRangeNr(0);
    m.setXYnr(0);
    m.setType('v');
    axisOutMappingList.append(m);
    //tryAxisMapToKey("vz1", 0, "tetrixleft");

    AxisOutMapper n;
    n.setAction("tetrixright");
    n.setAxis('x');
    n.setRangeNr(6);
    n.setXYnr(0);
    n.setType('v');
    axisOutMappingList.append(n);


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
    //controllerNo = 2;
    if (controllerNo == -1 || buttonList.isEmpty())
        return status;

    // if the source-button doesn't exist -> return
    if(!buttonList.contains(source.toLower()))
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



bool Mapper::tryAxisMapToKey(const QString axisName, const int range, const QString target) // axisName heeft formaat "PX1"
{
    bool status = false;
    // if no controller selected or the buttonlist is not filled -> return
    if (controllerNo == -1)
        return status;

    QChar type = axisName[0];
    QChar ax = axisName[1];
    QString nr = axisName[2];
    int xyNr = nr.toInt();

    // type = 'p' if we have a xy position
    if(type == 'p'){
        if(UsableControllers::getList()[controllerNo].getSensorXYList().size() <= xyNr){
            return status;
        }
        // check of this xy is fixed, if fixed -> buttons -> return
        if(UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getFixed()){
            return status;
        }
    }
    // type = 'v' if we have a xyz vector
    else if(type == 'v'){
        if(UsableControllers::getList()[controllerNo].getVectorList().size() <= xyNr){
            return status;
        }
    }
    // Is a button already mapped with this target?
    if (mappingList.contains(target.toLower()))
        return status;

    // Is the format already mapped? If not, use standard values
    int j = 0;
    bool mapped = false;
    while(j < axisFormatMapList.size()){
        if(axisFormatMapList[j].getAxisName() == axisName){
            mapped = true;

            // Check if the given range is smaller then the total number of ranges in mappingList
            if(range >= axisFormatMapList[j].getNumberOfRanges()){
                return status;
            }
        }
        j++;
    }
    // If not mapped: use standard values and add this format to axisFormatMapList
    if(!mapped){
        Axis axis;
        if(ax == 'x' && type == 'p'){
            axis = UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getXAxis();
        }
        else if(ax == 'y' && type == 'p'){
            axis = UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getYAxis();
        }
        if(ax == 'x' && type == 'v'){
            axis = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisX();
        }
        else if(ax == 'y' && type == 'v'){
            axis = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisY();
        }
        else if(ax == 'z' && type == 'v'){
            axis = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisZ();
        }
        else{
            return status;
        }
        AxisFormatMapper a;
        a.setAxisName(axisName);
        a.setNumberOfRanges(1);
        a.setRangeStart(axis.getRangeStart());
        a.setRangeEnd(axis.getRangeStop());
        a.setInverted(false);
        axisFormatMapList.append(a);
    }

    // Check if already mapped in axisOutMappingList, if mapped: return status false
    int i = 0;
    while(i < axisOutMappingList.size()){
        bool check = (axisOutMappingList[i].getControllerNr() == controllerNo) && (axisOutMappingList[i].getAxis() == ax) && (axisOutMappingList[i].getXYnr() == xyNr) && (axisOutMappingList[i].getRangeNr() == range);
        if(axisOutMappingList[i].getAction() == target || check){
            return status;
        }
        i++;
    }
    AxisOutMapper n;
    n.setAction(target);
    n.setAxis(ax);
    n.setRangeNr(range);
    n.setXYnr(xyNr);
    n.setType(type);
    axisOutMappingList.append(n);

    status = true;
    return status;
}


//
// Try to make a mapping to change the output format of the axis: change total range, divide in ranges (if no discrete ranges are wanted, range = 1)
// Possible to invert the output
//
bool Mapper::tryAxisFormatMap(const QString axisName, const int ranges, const int start, const int end, const bool inverted){

    bool status = false;

    // if no controller selected or the buttonlist is not filled -> return
    if (controllerNo == -1)
        return status;

    QChar ax = axisName[0];
    QString nr = axisName[1];
    int xyNr = nr.toInt();

    // Is there an axis with this name?
    if(UsableControllers::getList()[controllerNo].getSensorXYList().size() <= xyNr){
        return status;
    }
    // Check if the XY is variable(=axis) or not(= Buttons)
    if(UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getFixed()){
        return status;
    }

    // Check if there is already a mapping, if yes: change it
    int j = 0;
    bool mapped = false;
    while(j < axisFormatMapList.size()){
        if(axisFormatMapList[j].getAxisName() == axisName){
            mapped = true;
            axisFormatMapList[j].setNumberOfRanges(ranges);
            axisFormatMapList[j].setRangeStart(start);
            axisFormatMapList[j].setRangeEnd(end);
            axisFormatMapList[j].setInverted(inverted);
        }
        j++;
    }
    // Not mapped already: so add it
    if(!mapped){
        AxisFormatMapper a;
        a.setAxisName(axisName);
        a.setNumberOfRanges(ranges);
        a.setRangeStart(start);
        a.setRangeEnd(end);
        a.setInverted(inverted);
        axisFormatMapList.append(a);
    }

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
    //qDebug() << "Mapper::checkActions, actions: " << actions;
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
        //qDebug() << "Mapper::checkActions, buttonName: " << buttonName;

        if(buttonList.contains(buttonName))
        {
            action = mappingList.at(buttonList.indexOf(buttonName));
            emit actionHappened(action);
            //qDebug() << "Mapper: button action emitted";
        }
    }

    // Check if there are actions for some Axis values
    for(int i = 0; i < actionList.size(); i++){
        QString axisData = actionList[i].toLower();

        int j = 0;
        // Check the List with Format Changes
        while(j<axisFormatMapList.size()){
            QChar type = axisData[0]; // type (p = position, v = vector)
            QChar axis = axisData[1]; // axisname (x or y or z)
            if(axisData.contains('_')){
                if(type == 'p' || type == 'v'){
                    if(axis == 'x' || axis == 'y' || axis == 'z'){
                        QStringList axisList;
                        axisList = axisData.split('_'); // split (axis name + nr) from it's value
                        QString axisName = axisList[0];
                        float value = axisList[1].toInt();
                        // inverted?
                        if(axisFormatMapList[j].isInverted()){
                            value = invertRange(value);
                        }
                        QString xyNr = axisName.at(2);
                        int xy = xyNr.toInt(); // in case of a vector this is the vectorNr

                        // change te value to the mapped format
                        value = valueInNewRange(type, axis, xy, axisFormatMapList[j].getRangeStart(), axisFormatMapList[j].getRangeEnd(), value);

                        // Is there a change in value?
                        if((axisName == axisFormatMapList[j].getAxisName()) && (value != axisFormatMapList[j].getLastValue())){
                            axisFormatMapList[j].setLastValue(value);
                            float div = (axisFormatMapList[j].getRangeEnd() - axisFormatMapList[j].getRangeStart())/axisFormatMapList[j].getNumberOfRanges();
                            if(axisFormatMapList[j].getNumberOfRanges() > 1){
                                float k = 0;
                                // What range?
                                while(k < axisFormatMapList[j].getNumberOfRanges()){
                                    float value2 = axisFormatMapList[j].getRangeStart() + (k+1)*(div);
                                    if(value <= value2){
                                        // Change in range?
                                        if(axisFormatMapList[j].getLastRange() != k){
                                            axisFormatMapList[j].setLastRange(k);
                                            int l = 0;
                                            // Check the Output Mapping List
                                            while(l < axisOutMappingList.size()){
                                                if(axisOutMappingList[l].getRangeNr() == k && xy == axisOutMappingList[l].getXYnr() && axis == axisOutMappingList[l].getAxis()){
                                                    emit actionHappened(axisOutMappingList[l].getAction());
                                                    qDebug() << "Mapper: axis action emitted";
                                                    l = axisOutMappingList.size();
                                                }
                                                l++;
                                            }
                                        }
                                        k=axisFormatMapList[j].getNumberOfRanges();
                                        j = j<axisFormatMapList.size();
                                    }
                                    else
                                    {
                                        k++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            j++;
        }
    }
}



// Change the value of the axis to the format
float Mapper::valueInNewRange(QChar type, QChar axis, int xyNr, int newStart, int newStop, float value){
    Axis ax;

    if (controllerNo == -1)
        return value;

    if(axis == 'x' && type == 'p'){
        ax = UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getXAxis();
    }
    else if(axis == 'y' && type == 'p'){
        ax = UsableControllers::getList()[controllerNo].getSensorXYList()[xyNr].getYAxis();
    }
    else if(axis == 'x' && type == 'v'){
        ax = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisX();

    }
    else if(axis == 'y' && type == 'v'){
        ax = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisY();
    }
    else if(axis == 'z' && type == 'v'){
        ax = UsableControllers::getList()[controllerNo].getVectorList()[xyNr].getAxisZ();
    }

    int oldRange = ax.getRangeStop() - ax.getRangeStart();
    int newRange = newStop - newStart;
    value = value + newStart - ax.getRangeStart();
    float delen = (float) newRange/oldRange;
    float value2 = value*(delen);
    return value2;
}

// Invert the range of the axis
float Mapper::invertRange(float value){
    float value2 = (-1)*value;
    return value2;
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


