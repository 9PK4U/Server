#pragma once
#include <map>
#include <QDebug>
#include <QTcpsocket>
#include "User.h"
#include "../ServerController/OperationParser.h"
#include "../ServerController/OperationCreator.h"
#include "Game.h"
using std::map;
using Client = QPair<int, QTcpSocket*>;
class GameCore : public QObject
{
	Q_OBJECT
	QMap<int,QPair<Client*, User*>> *autorizationUsers;
	QMap<int, QPair<Client*, User*>> *findGameUsers;
	QMap<int, Game*> *activeGames;


signals:
	void connectUser();
public:
	GameCore();
	void showActiveUsers();
	bool findGame(int id);
	bool enterCell(int id, int index);
	bool autorization(Client* client, string login, string password);
	bool registration(string login, string password);
	bool getStatictic(int id);
	bool endGame(int id);
private slots:
	void startGame();
	
};

