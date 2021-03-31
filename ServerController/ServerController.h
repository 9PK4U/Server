#pragma once

#include <qtcpsocket.h>
#include "OperationParser.h"
#include "OperationCreator.h"

using namespace std;

using Client = QPair<int, QTcpSocket*>;
using ClientList = QMap<int, Client*>;
class ServerController :
	public QObject
{
	Q_OBJECT
public:
	ServerController(QObject* parent = nullptr);
	ClientList* clientList;

	void requestProcessor(int id, QByteArray arrayJsonData);

	//void operationProcessor(int id, Operation operation);
	void response(int clientId, Operation operation);

public slots:
	void request(int clientId);

signals:
	void newOperation(int idClient, Operation operation);

};

