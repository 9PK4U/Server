#include "Server.h"


Server::Server(QObject* parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if (!server->listen(QHostAddress::Any, 6000)) {
        writeToLog("Not started");
        throw std::exception("Server is not started!");
    }

    clientList = new SocketList();
    controller = new ServerController(clientList,this);

    writeToLog("Started");
}

void Server::slotNewConnection()
{
    //connect(mTcpSocket, &QTcpSocket::readyRead, this, &Server::slotServerRead);
    //connect(mTcpSocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);

    writeToLog("New connected!");

    QTcpSocket* sock = server->nextPendingConnection();
    int id = sock->socketDescriptor();
    (*clientList)[id] = sock;

    connect((*clientList)[id], &QTcpSocket::readyRead, controller, [=]() { controller->request(id); });


}

void Server::writeToLog(QString message)
{
    qDebug() <<"Server: "<< message;
}
