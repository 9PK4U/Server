#pragma once
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include "ServerController.h"


class Server :
    public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);

public slots:
    void slotNewConnection();

    

private:
    QTcpServer* server;
    SocketList* clientList;
    ServerController *controller;

    void writeToLog(QString message);
};


