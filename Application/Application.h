#pragma once
#include "../ServerController/ServerController.h"
#include "User.h"
#include "../Game/Game.h"
#include <qobject.h>
#include <string>
class Application : public QObject
{
	Q_OBJECT

public:
	Application(ServerController& controller);
private:
	QMap<int, User*>* autorizationUsers;
	QVector<User*>* findGameUsers;
	QMap<int, Game*>* activeGames;

	ServerController& controller;
	void operationProcessor(int id, Operation operation);


	///Handle functions
	void autorization(int idClient, Parametrs parametrs);
	void registration(int idClient, Parametrs parametrs);
	void findGame(int idClient, Parametrs parametrs);
	void enterCell(int idClient, Parametrs parametrs);

	//Checks function
	bool checkAutorization(int& idClient);
	Game* checkGame(int& idClient, int idGame);
	



signals:
	void newSearchUser();
private slots:
	void startNewGame();

};

