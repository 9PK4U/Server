#include "ServerController.h"

void ServerController::processor(int id, QByteArray arrayJsonData)
{
    try
    {
        QJsonDocument document = QJsonDocument::fromJson(arrayJsonData);
        auto operation = OperationParser::JsonToOperation(document);

        qDebug() << QString::fromStdString(operation.toString());


        response(id, operation);
    }
    catch (const std::exception& ex)
    {
        log(ex.what());
        response(id, OperationCreator::createErrorResponse(ex.what()));
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
            processor(id , array);
        }
}
