#ifndef RUN_H
#define RUN_H

#include <QThread>
class Run : public QThread
{
    Q_OBJECT
public:
    Run(QObject *parent);
    void run();
};

#endif // RUN_H
