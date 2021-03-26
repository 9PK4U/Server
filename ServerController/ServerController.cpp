#include "ServerController.h"

void ServerController::requestProcessor(int id, QByteArray arrayJsonData)
{
    try
    {
        QJsonDocument document = QJsonDocument::fromJson(arrayJsonData);
        auto operation = OperationParser::JsonToOperation(document);

        qDebug() << QString::fromStdString(operation.toString()); //DELETE


        operationProcessor(id, operation);
    }
    catch (const std::exception& ex)
    {
        log(ex.what());
        response(id, OperationCreator::createErrorResponse(ex.what()));
    }

}

void ServerController::operationProcessor(int id, Operation operation)
{
    //TEMP
    if (operation.getType() == Operation::Type::FindGame)
    {
        Player* player = new Player(std::to_string(id));
        players[id] = player;

    }
    if (game == nullptr && players.size() > 1)
    {
        game = new Game(players.first(), players.last());
        qDebug() << "GAME CREATED";
    }
    if (game != nullptr)
    {
        if (operation.getType() == Operation::Type::EnterCell)
        {
            game->step(std::stoi(operation.getParametr("Index")));
        }
        auto context = game->getContext();

        qDebug() << QString::fromStdString(context.currentStepPlayerName) << QString::fromStdString(context.player1Points) << QString::fromStdString(context.player2Points) << QString::fromStdString(context.map) << '\n';
    }
}

ServerController::ServerController(SocketList* clientList, QObject* parent) : clientList(clientList)
{

}

void ServerController::log(QString message)
{
    qDebug() <<QTime::currentTime() <<" ServerController: " << message <<'\n';
}

void ServerController::response(int id, Operation operation)
{
    auto& client = (*clientList)[id];
    auto res = OperationParser::OperationToJson(operation);
    log("Response to " + QString::number(id) + " Data: " + res);
    client->write(QString::fromStdString(operation.toString()).toUtf8());
}

void ServerController::request(int id)
{
    auto& client = (*clientList)[id];
        while (client->bytesAvailable() > 0)
        {
            QByteArray array = client->readAll();
            log("Request from " + QString::number(id) + " Data: " + array);
            requestProcessor(id , array);
        }
}
