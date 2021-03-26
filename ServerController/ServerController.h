#pragma once

#include <qtcpsocket.h>
#include "OperationParser.h"
#include "OperationCreator.h"

using namespace std;

using SocketList = QMap<int, QTcpSocket*>;
class ServerController :
	public QObject
{
	Q_OBJECT
public:

	void processor(int id, QByteArray arrayJsonData);
	
	ServerController(SocketList* clientList, QObject* parent = nullptr);


private:

	SocketList* clientList;
	void log(QString message);

	void response(int id, Operation operation);
public slots:
	void request(int id);

};

