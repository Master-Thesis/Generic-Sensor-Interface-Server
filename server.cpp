#include <QtGui>
#include <QtNetwork>
#include <windows.h>

#include "udpserver.h"
#include "mapper.h"
#include "server.h"
#include "temp/handledevice.h"

Server::Server(QWidget *parent) :
    QDialog(parent)
{
    InitRawInput();

    statusLabel = new QLabel(tr("Click 'Start' to start the UDP server"));

    startButton = new QPushButton(tr("&Start"));
    quitButton = new QPushButton(tr("&Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    //UDPServer initialisation
    udpServer = new UDPServer(this);
    udpServer->setOtherNodePort(50001);

    connect(startButton, SIGNAL(clicked()), udpServer, SLOT(startSocket()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(Mapper::instance(), SIGNAL(actionHappened(QString)), udpServer, SLOT(sendControllerAction(QString)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("UDP Protocol Based Server"));
}

Server::~Server()
{

}

void Server::InitRawInput() {
    RAWINPUTDEVICE Rid[10]; // allocate storage for 10 device
    UINT nDevices;
    PRAWINPUTDEVICELIST pRawInputDeviceList;
    if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) {
            return;
    }
    pRawInputDeviceList = (RAWINPUTDEVICELIST *)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices);
    GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

    // after the job, free the RAWINPUTDEVICELIST
    free(pRawInputDeviceList);

    // add Game pad
    Rid[0].usUsagePage = 0x01;
    Rid[0].usUsage = 0x05;
    Rid[0].dwFlags = 0;
    Rid[0].hwndTarget = 0;

    // add Keyboard
    Rid[1].usUsagePage = 0x01;
    Rid[1].usUsage = 0x06;
    Rid[1].dwFlags = RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
    Rid[1].hwndTarget = 0;

    // add Mouse
//    Rid[2].usUsagePage = 0x01;
//    Rid[2].usUsage = 0x02;
//    Rid[2].dwFlags = RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
//    Rid[2].hwndTarget = NULL;

    if (RegisterRawInputDevices(Rid, 2, sizeof (Rid [0])) == FALSE) {
            printf("RawInput init failed:\n");
            //registration failed.
    }
    return ;
}

bool Server::winEvent(MSG *m, long *result)
{
    //printf("Winevent\n");
    //m->lParam

//    HandleDevice *thread = new HandleDevice(m, result, this);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
//    thread->start();
//    return true;

    if(WM_INPUT == m->message){
        HandleDevice *t = new HandleDevice(m, result, this);
        connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
        connect(t,SIGNAL(buttonAction(QString)), Mapper::instance(), SLOT(checkActions(QString)));
        t->start();
        t->wait();
        //return QWidget::winEvent(m, result);
        return true;
    }
    else{
        return false;
    }
}

