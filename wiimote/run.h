#ifndef RUN_H
#define RUN_H

#include <QThread>
#include <QString>

class Run : public QThread
{
    Q_OBJECT
public:
//    static Run* instance();
//    static void drop();

    Run(QObject *parent);
    void run();

public slots:
    void actionWii(const QString act);

//private:
//    //explicit Run(QObject *parent = 0);
//    virtual ~Run(){}
//    //void initQStringList(QList<QString> &list, const int size);

//    static Run *m_mapper;

signals:
    void sendActionWii(QString stateMessage);
};

#endif // RUN_H
