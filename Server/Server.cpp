#include "Server.h"


Server::Server(QObject* parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::newClient);

    if (!server->listen(QHostAddress::Any, 6000)) {
        writeToLog("Not started");
        throw std::exception("Server is not started!");
    }

    controller = new ServerController(this);

    writeToLog("Started");
}

void Server::newClient()
{
    QTcpSocket* sock = server->nextPendingConnection();
    qintptr id = sock->socketDescriptor();
    (*controller->clientList)[id] = new Client(id,sock);

    connect(sock, &QTcpSocket::readyRead, controller, [=]() { controller->request(id); });
    connect(sock, &QTcpSocket::disconnected, this, &Server::disconnectClient);

    writeToLog(QString("ID: ") + QString::number(id) + " is connected");
}

void Server::disconnectClient()
{
    qDebug() << "Disconect ";
}

void Server::writeToLog(QString message)
{
    qDebug() <<"Server: "<< message;
}
ServerController& Server::getController() const
{
    return *controller;
}