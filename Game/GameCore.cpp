#include "GameCore.h"
#include <QFile>
//DELETE
//GameCore::GameCore()
//{
//	autorizationUsers = new QMap<int, QPair<Client*, User*>>();
//	findGameUsers = new QMap<int, QPair<Client*, User*>>();
//	activeGames = new QMap<int, Game*>();
//
//	connect(this, &GameCore::connectUser, this, &GameCore::startGame);
//
//}
//
//void GameCore::showActiveUsers()
//{
//	for (auto i : *autorizationUsers)
//		qDebug() << "ID:" << i.first << " Login:" << QString::fromStdString(i.second->getLogin() + " Points:" + i.second->getGeneralPoints());
//}
//
//bool GameCore::autorization(Client* client, string login, string password)
//{
//
//	QFile file("User.txt");
//	if (file.open(QIODevice::ReadOnly)) {
//
//		while (!file.atEnd())
//		{
//			QString str = file.readLine();
//			QStringList lst = str.split(" ");
//			std::string loginFile = lst.at(0).toUtf8().constData();//Login
//			std::string passwordFile = lst.at(1).toUtf8().constData();//Password
//
//			if (login == loginFile && (password  == passwordFile || password+"\r\n" == passwordFile ))
//			{
//				User* user = new User(login);
//				auto p = QPair<Client*, User*>(client, user);
//				autorizationUsers->operator[](client->first) = p;
//				showActiveUsers();
//				file.close();
//				return true;
//
//			}
//		}
//		file.close();
//		return false;
//		
//	}
//	else
//	{
//		qDebug() << "Error FILE";
//	}
//
//}
//
//bool GameCore::registration(Client * client, string login, string password)
//{
//	string finishStr;
//	QFile file("User.txt");
//	if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
//
//		while (!file.atEnd())
//		{
//			QString str = file.readLine();
//			QStringList lst = str.split(" ");
//			std::string loginFile = lst.at(0).toUtf8().constData();//Login
//			std::string passwordFile = lst.at(1).toUtf8().constData();//Password
//
//			if (login == loginFile)
//			{
//				file.close();
//				return false;
//			}
//		}
//		//Запись в файл
//		finishStr = login + " " + password+"\n";
//		QString str = QString::fromStdString(finishStr);
//		QTextStream writeStream(&file);
//		writeStream << str;
//		file.close();
//		return true;
//		
//	}
//	else
//	{
//		qDebug() << "Error FILE";
//	}
//}
//
//bool GameCore::findGame(int id)
//{
//	if (autorizationUsers->find(id) != autorizationUsers->end())
//	{
//		findGameUsers->operator[](id) = autorizationUsers->operator[](id);
//		emit connectUser();
//		return true;
//	}
//	return false;
//}
//bool GameCore::enterCell(int id, int index)
//{
//	auto client = autorizationUsers->find(id);
//	if (client == autorizationUsers->end())
//	{
//		return false;
//	}
//	for (auto i : *activeGames)
//	{
//		if (i->getStepPlayer()->name == (*client).second->getLogin())
//		{
//			i->step(index);
//			client.operator*().first->second->write(OperationParser::OperationToJson(OperationCreator::createEnterCellResponse(i->getContext().lastPoint, i->getContext().map)));
//		}
//	}
//
//	return true;
//}
//void GameCore::startGame()
//{
//	if (findGameUsers->size() > 1)
//	{
//		auto cl1 = findGameUsers->first().first;
//		auto cl2 = findGameUsers->last().first;
//		Player* pl1 = new Player(findGameUsers->operator[](cl1->first).second->getLogin());
//		Player* pl2 = new Player(findGameUsers->operator[](cl2->first).second->getLogin());
//		Game* game = new Game(pl1, pl2);
//		qDebug() << "GAME START"; //DEBUG
//
//		cl1->second->write(OperationParser::OperationToJson(OperationCreator::createFindGameResponse("0",
//			pl1->name,
//			pl2->name,
//			game->getContext().map,
//			game->getContext().currentStepPlayerName)));
//		cl2->second->write(OperationParser::OperationToJson(OperationCreator::createFindGameResponse("0",
//			pl1->name,
//			pl2->name,
//			game->getContext().map,
//			game->getContext().currentStepPlayerName)));
//		activeGames->operator[](0) = game;
//	}
//}