#include "ServerController.h"

QByteArray ServerController::processor(int id, QByteArray array)
{
	QJsonDocument document = QJsonDocument::fromJson(array);
    OperationParser::JsonToOperation(document);
	return array;

}

ServerController::ServerController(SocketList* clientList, QObject* parent) : clientList(clientList)
{
}

void ServerController::log(QString message)
{
    qDebug() << "ServerController: " << message;
}

void ServerController::request(int id)
{
    auto& client = (*clientList)[id];
        while (client->bytesAvailable() > 0)
        {
            QByteArray array = client->readAll();

            // mTcpSocket->write(array);
            log("Request from " + QString::number(id) + " Data: " + array);

            auto res = processor(id , array);
            log("Response to " + QString::number(id) + " Data: " + res);
            client->write(res);


        }
}
