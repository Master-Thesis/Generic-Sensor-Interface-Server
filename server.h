#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

#include "temp/handledevice.h"
#include "udpserver.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    virtual ~Server();
    //RAWINPUTDEVICE Rid[50];

public slots:

signals:

protected:
    bool winEvent(MSG *m, long *result);

private:
    void InitRawInput();

    Mapper *mapper;
    UDPServer *udpServer;
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;

};

#endif // SERVER_H
