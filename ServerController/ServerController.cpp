#include "ServerController.h"

void ServerController::requestProcessor(int id, QByteArray arrayJsonData)
{
    try
    {
        QJsonDocument document = QJsonDocument::fromJson(arrayJsonData);
        auto operation = OperationParser::JsonToOperation(document);

        qDebug() << "INPUT DATA" << QString::fromStdString(operation.toString()) <<'\n'; //DELETE


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
    auto client = (*clientList)[id];
    switch (operation.getType())
    {
    case Operation::Type::Autorization:
        gameCore->autorization(client,operation.getParametr("Login"), operation.getParametr("Password"));
        break;
    case Operation::Type::Registration:
        break;
    case Operation::Type::EnterCell:
        gameCore->enterCell(id, std::stoi(operation.getParametr("Index")));
        break;
    case Operation::Type::GetStatistic:
        break;
    case Operation::Type::FindGame:
        gameCore->findGame(id);
        break;
    case Operation::Type::EndGame:
        break;
    case Operation::Type::StatusGame:
        break;
    case Operation::Type::Error:
        break;
    default:
        break;
    }
}

ServerController::ServerController(ClientList* clientList, QObject* parent) : clientList(clientList)
{
    gameCore = new GameCore();
}

void ServerController::log(QString message)
{
    qDebug() <<QTime::currentTime() <<" ServerController: " << message <<'\n';
}

void ServerController::response(int id, Operation operation)
{
    auto client = (*clientList)[id];
    auto res = OperationParser::OperationToJson(operation);
    log("Response to " + QString::number(id) + " Data: " + res);
    client->second->write(QString::fromStdString(operation.toString()).toUtf8());
}

void ServerController::request(int id)
{
    auto client = (*clientList)[id];
        while (client->second->bytesAvailable() > 0)
        {
            QByteArray array = client->second->readAll();
            log("Request from " + QString::number(id) + " Data: " + array);
            requestProcessor(id , array);
        }
}
