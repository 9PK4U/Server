#pragma once
#include "Operation.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class OperationParser
{
public:
	static Operation JsonToOperation(QJsonDocument document);
};

