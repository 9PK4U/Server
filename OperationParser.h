#pragma once
#include "Operation.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class OperationParser
{
public:
	static Operation JsonToOperation(QJsonDocument document);
	static QByteArray OperationToJson(Operation operation);

private:
	static bool validKeys(QStringList& keys);
	static bool validParametrs(QJsonValueRef& parametrs);
	static Operation::Type getType(QJsonValueRef& operation);




};

