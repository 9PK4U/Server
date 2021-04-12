#include "ServerController.h"

void ServerController::requestProcessor(int id, QByteArray arrayJsonData)
{
    try
    {
        QJsonDocument document = QJsonDocument::fromJson(arrayJsonData);
        auto operation = OperationParser::JsonToOperation(document);

        qDebug() << "\n" <<"ServerController::INPUT PARSE DATA: " << QString::fromStdString(operation.toString()); //DELETE
;
        emit newOperation(id, operation);

    }
    catch (const std::exception& ex)
    {
        qDebug() << QString("ServerController: ") + ex.what();
        response(id, OperationCreator::createErrorResponse(ex.what()));
    }

}

ServerController::ServerController(QObject* parent)
{
    clientList = new ClientList();
}

void ServerController::response(int id, Operation operation)
{
    auto client = (*clientList)[id];
    auto res = OperationParser::OperationToJson(operation);
    qDebug() << "\n" <<"ServerController::Response to " << QString::number(id) << " Data: " << res;
    client->second->write(res);
}

void ServerController::request(int id)
{
    auto client = (*clientList)[id];
        while (client->second->bytesAvailable() > 0)
        {
            QByteArray array = client->second->readAll();
            qDebug() << "\n" << "ServerController::Request from " << QString::number(id) << " Data: " << array;
            requestProcessor(id , array);
        }
}
