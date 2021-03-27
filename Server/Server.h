#pragma once
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <QDebug>
#include <QCoreApplication>

#include "../ServerController/ServerController.h"


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
    ClientList* clientList;
    ServerController *controller;

    void writeToLog(QString message);
};

