#ifndef MAPPER_H
#define MAPPER_H

#include <QObject>

#include "temp/button.h"
#include "temp/usablecontrollers.h"

class Mapper : public QObject
{
    Q_OBJECT

public:
    static Mapper* instance();
    static void drop();

    static int getSelectedControllerNo(){return controllerNo;}
    static Controller getSelectedController();

    static bool tryDeviceSelect(const int deviceNo);
    static bool tryDeviceDeselect(const int newDevice = -1);
    static bool tryKeyMap(const QString source, const QString target);
    static bool tryUndoKeyMap(const QString target);

signals:
    void actionHappened(QString button);

public slots:
    void checkActions(const QString actions);

private:
    explicit Mapper(QObject *parent = 0);
    virtual ~Mapper();
    void initQStringList(QList<QString> &list, const int size);

    static Mapper *m_mapper;
    static int controllerNo;
    static QList<QString> buttonList;
    static QList<QString> mappingList;

};

#endif // MAPPER_H
