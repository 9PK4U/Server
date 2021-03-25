#include "Server.h"
#include <QDebug>
#include <QCoreApplication>


#include "ServerController.h"

Server::Server(QObject* parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if (!server->listen(QHostAddress::Any, 6000)) {
        qDebug() << "server is not started";
    }
    else {
        qDebug() << "server is started";
    }
}

void Server::slotNewConnection()
{
    //mTcpSocket = server->nextPendingConnection();

 /*   mTcpSocket->write("Hello, World!!! I am echo server!\r\n");

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &Server::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);*/

    qDebug() << QString::fromUtf8("new connected!");
    QTcpSocket* clientSocket = server->nextPendingConnection();
    int idusersocs = clientSocket->socketDescriptor();
    SClients[idusersocs] = clientSocket;
    connect(SClients[idusersocs], SIGNAL(readyRead()), this, SLOT(slotServerRead()));
}

void Server::slotServerRead()
{
    foreach(int i, SClients.keys())
    while (SClients[i]->bytesAvailable() > 0)
    {
        QByteArray array = SClients[i]->readAll();

       // mTcpSocket->write(array);
        qDebug() << array;

        ServerController cont;
        auto res = cont.handle(array);
        qDebug() << "res" << res;
        SClients[i]->write(res);

        
    }
}

void Server::slotClientDisconnected()
{
    qDebug() << "disConnect";
    //mTcpSocket->close();
}

void Server::slotClientConnected()
{
   
    //mTcpSocket->write(QString("hi").toUtf8());
}