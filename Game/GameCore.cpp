#include "GameCore.h"

GameCore::GameCore()
{
	autorizationUsers = new QMap<int, QPair<Client*, User*>>();
	findGameUsers = new QMap<int, QPair<Client*, User*>>();
	activeGames = new QMap<int,Game*>();

	connect(this, &GameCore::connectUser, this, &GameCore::startGame);

}

void GameCore::showActiveUsers()
{
	for (auto i : *autorizationUsers)
		qDebug() << "ID:" << i.first << " Login:" << QString::fromStdString(i.second->getLogin() + " Points:" + i.second->getGeneralPoints());
}

bool GameCore::autorization(Client* client, string login, string password)
{
	User* user = new User(login);
	auto p = QPair<Client*, User*>(client, user);
	autorizationUsers->operator[](client->first) = p;
	showActiveUsers();
	return true;
}

bool GameCore::findGame(int id)
{
	if (autorizationUsers->find(id) != autorizationUsers->end())
	{
		findGameUsers->operator[](id) = autorizationUsers->operator[](id);
		emit connectUser();
		return true;
	}
	return false;
}
bool GameCore::enterCell(int id, int index)
{
	auto client = autorizationUsers->find(id);
	if (client == autorizationUsers->end())
	{
		return false;
	}
	for (auto i : *activeGames)
	{
		if (i->getStepPlayer()->name == (*client).second->getLogin())
		{
			i->step(index);
			client.operator*().first->second->write(OperationParser::OperationToJson(OperationCreator::createEnterCellResponse(i->getContext().lastPoint, i->getContext().map)));
		}
	}

	return true;
}
void GameCore::startGame()
{
	if (findGameUsers->size() > 1)
	{
		auto cl1 = findGameUsers->first().first;
		auto cl2 = findGameUsers->last().first;
		Player* pl1 = new Player(findGameUsers->operator[](cl1->first).second->getLogin());
		Player* pl2 = new Player(findGameUsers->operator[](cl2->first).second->getLogin());
		Game* game = new Game(pl1, pl2);
		qDebug() << "GAME START"; //DEBUG

		cl1->second->write(OperationParser::OperationToJson(OperationCreator::createFindGameResponse("0",
			pl1->name,
			pl2->name,
			game->getContext().map,
			game->getContext().currentStepPlayerName)));
		cl2->second->write(OperationParser::OperationToJson(OperationCreator::createFindGameResponse("0",
			pl1->name,
			pl2->name,
			game->getContext().map,
			game->getContext().currentStepPlayerName)));
		activeGames->operator[](0) = game;
	}
}