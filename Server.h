#pragma once
#include <qobject.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
class Server :
    public QObject
{

  
    Q_OBJECT
public:
    explicit Server(QObject* parent = 0);

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();
    void slotClientConnected();

    

private:
    QTcpServer* server;
    

    QMap<int, QTcpSocket*> SClients;
};


