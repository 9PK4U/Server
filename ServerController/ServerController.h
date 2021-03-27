#pragma once

#include <qtcpsocket.h>
#include "OperationParser.h"
#include "OperationCreator.h"
#include "../Game/GameCore.h"

using namespace std;


using ClientList = QMap<int, Client*>;
class ServerController :
	public QObject
{
	Q_OBJECT
public:

	void requestProcessor(int id, QByteArray arrayJsonData);
	void operationProcessor(int id, Operation operation);
	
	ServerController(ClientList* clientList, QObject* parent = nullptr);


private:
	GameCore* gameCore;
	ClientList* clientList;
	void log(QString message);

	void response(int id, Operation operation);
public slots:
	void request(int id);

};

