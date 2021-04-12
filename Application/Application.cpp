#include "Application.h"
#include <QFile>

Application::Application(ServerController& controller) : controller(controller)
{
    findGameUsers       = new QVector<User*>();
    autorizationUsers   = new QMap<int, User*>();
    activeGames         = new QMap<int, Game*>();
    QObject::connect(&controller, &ServerController::newOperation, this, &Application::operationProcessor);
    QObject::connect(this, &Application::newSearchUser, this, &Application::startNewGame);
}

void Application::operationProcessor(int id, Operation operation)
{
    switch (operation.getType())
    {
    case Operation::Type::Autorization:
        autorization(id, operation.getParametrs());
        break;
    case Operation::Type::Registration:
        registration(id, operation.getParametrs());
        break;
    case Operation::Type::EnterCell:
        enterCell(id, operation.getParametrs());
        break;
    case Operation::Type::GetStatistic:
        qDebug() << "Not command";
        break;
    case Operation::Type::FindGame:
        findGame(id, operation.getParametrs());
        break;
    case Operation::Type::EndGame:
        qDebug() << "Not command";
        break;
    case Operation::Type::StatusGame:
        qDebug() << "Not command";
        break;
    case Operation::Type::Error:
        qDebug() << "Not command";
        break;
    default:
        break;
    }
}

void Application::autorization(int idClient, Parametrs parametrs)
{
    if (parametrs.find("Login") == parametrs.end()
        || parametrs.find("Password") == parametrs.end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        return;
    }
    auto login = parametrs["Login"];
    auto password = parametrs["Password"];


    QFile file("User.txt");
    if (file.open(QIODevice::ReadOnly)) {

        while (!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(" ");
            std::string loginFile = lst.at(0).toUtf8().constData();//Login
            std::string passwordFile = lst.at(1).toUtf8().constData();//Password

            if (login == loginFile && (password == passwordFile || password + "\r\n" == passwordFile))
            {
                (*autorizationUsers)[idClient] = new User(login, idClient);
                file.close();
                controller.response(idClient, OperationCreator::createAutorizationResponse(Process::Success));
                return;

            }
        }
        file.close();

    }
    else
    {
        qDebug() << "Error FILE";
    }
    controller.response(idClient, OperationCreator::createAutorizationResponse(Process::Failed));
}

void Application::registration(int idClient, Parametrs parametrs)
{
    if (parametrs.find("Login") == parametrs.end()
        || parametrs.find("Password") == parametrs.end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        return;
    }

    auto login = parametrs["Login"];
    auto password = parametrs["Password"];

    string finishStr;
    QFile file("User.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {

        while (!file.atEnd())
        {
            QString str = file.readLine();
            QStringList lst = str.split(" ");
            std::string loginFile = lst.at(0).toUtf8().constData();//Login
            std::string passwordFile = lst.at(1).toUtf8().constData();//Password

            if (login == loginFile)
            {
                file.close();
                controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Failed));
                return;
            }
        }
        //Запись в файл
        finishStr = login + " " + password + "\n";
        QString str = QString::fromStdString(finishStr);
        QTextStream writeStream(&file);
        writeStream << str;
        file.close();
        controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Success));
        return;

    }
    else
    {
        qDebug() << "Error FILE";
    }
    controller.response(idClient, OperationCreator::createRegistrationResponse(Process::Failed));
}

void Application::findGame(int idClient, Parametrs parametrs)
{
    if (!checkAutorization(idClient)) return;
    auto user = (*autorizationUsers)[idClient];
    (*findGameUsers)[idClient] = user;
    emit newSearchUser();
}

bool Application::checkAutorization(int& idClient)
{

    if (autorizationUsers->find(idClient) == autorizationUsers->end())
    {
        controller.response(idClient, OperationCreator::createErrorResponse("To access, you need to log in"));
        return false;
    }
    return true;
}
Game* Application::checkGame(int& idClient, int idGame)
{
    try
    {

        auto game = (*activeGames)[idGame];
        if (game != nullptr && checkAutorization(idClient))
        {
            auto names = game->getNamesPlayers();
            auto namePlayer = (*autorizationUsers)[idGame]->getLogin();
            if (names.second == namePlayer || names.first == namePlayer)
            {
                return game;
            }
        }
        else
        {
            controller.response(idClient, OperationCreator::createErrorResponse("Game with such a player was not found"));
            return nullptr;
        }

    }
    catch (const std::exception& ex)
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Game with such a player was not found"));
        throw ex;
    }
}

void Application::startNewGame()
{
    static int countGame = 0;
    if (findGameUsers->size() < 2) return;

    auto user1 = findGameUsers->takeFirst();
    auto user2 = findGameUsers->takeFirst();

    Player* player1 = new Player(user1->getLogin());
    Player* player2 = new Player(user2->getLogin());
    Game* game = new Game(player1, player2);
    (*activeGames)[countGame] = game;
    controller.response(user1->getId(), OperationCreator::createFindGameResponse(QString::number(countGame).toStdString(), 
        player1->name,
        player2->name,
        game->getContext().currentStepPlayerName));
    controller.response(user2->getId(), OperationCreator::createFindGameResponse(QString::number(countGame).toStdString(), 
        player1->name,
        player2->name,
        game->getContext().currentStepPlayerName));
}

void Application::enterCell(int idClient, Parametrs parametrs)
{
    try
    {
        auto game = checkGame(idClient, std::stoi(parametrs["Id"]));
        if (game == nullptr) return;

        if (game->getStepPlayer()->name == (*autorizationUsers)[idClient]->getLogin())
        {
            int index = std::stoi(parametrs["Index"]);
            game->step(index);
            controller.response(idClient, OperationCreator::createEnterCellResponse(game->getContext()));
        }
        else
        {
            controller.response(idClient, OperationCreator::createErrorResponse("Not your step"));
        }
    }
    catch (const std::exception& ex)
    {
        controller.response(idClient, OperationCreator::createErrorResponse("Incorrect parametrs"));
        qDebug() << QString("Application::enterCell: ") + ex.what();
    }

}

