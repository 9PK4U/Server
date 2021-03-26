#pragma once

#include <qtcpsocket.h>
#include "OperationParser.h"

using namespace std;

using SocketList = QMap<int, QTcpSocket*>;
class ServerController :
	public QObject
{
	Q_OBJECT
public:

	QByteArray processor(int id, QByteArray array);
	
	ServerController(SocketList* clientList, QObject* parent = nullptr);


private:

	SocketList* clientList;
	void log(QString message);

public slots:
	void request(int id);

};

