#pragma once
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <QDebug>
#include <QCoreApplication>

#include "../ServerController/ServerController.h"


#define PORT 6000

class Server :
    public QObject
{
    Q_OBJECT
public:
    ServerController& getController() const;
    explicit Server(QObject* parent = nullptr);

public slots:
    void newClient();
    void disconnectClient();

    

private:
    ServerController* controller;
    QTcpServer* server;

    void writeToLog(QString message);
};


