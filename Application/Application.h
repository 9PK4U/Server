#pragma once
#include "../ServerController/ServerController.h"
#include "User.h"
#include "../Game/Game.h"
#include <qobject.h>
class Application : public QObject
{
	Q_OBJECT

public:
	Application(ServerController& controller);
private:
	QMap<int, User*>* autorizationUsers;
	QMap<int, User*>* findGameUsers;
	QMap<int, Game*>* activeGames;

	ServerController& controller;
	void operationProcessor(int id, Operation operation);

	void autorization(int idClient, Parametrs parametrs);
	void registration(int idClient, Parametrs parametrs);
	void findGame(int idClient, Parametrs parametrs);
	void startGame(int idClient1, int idClient2);
	void enterCell(int idClient, Parametrs parametrs);

};

