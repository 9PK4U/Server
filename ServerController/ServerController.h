#pragma once

#include <qtcpsocket.h>
#include "OperationParser.h"
#include "OperationCreator.h"
#include "../Game/Game.h"

using namespace std;

using SocketList = QMap<int, QTcpSocket*>;
class ServerController :
	public QObject
{
	Q_OBJECT
public:

	void requestProcessor(int id, QByteArray arrayJsonData);
	void operationProcessor(int id, Operation operation);
	
	ServerController(SocketList* clientList, QObject* parent = nullptr);


private:
	//////////////////////////////// TEMP
	QMap<int, Player*> players;
	Game *game = nullptr;

	////////////////////////////////
	SocketList* clientList;
	void log(QString message);

	void response(int id, Operation operation);
public slots:
	void request(int id);

};

