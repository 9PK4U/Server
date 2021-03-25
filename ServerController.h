#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using namespace std;
class ServerController
{
public:
	bool map[16]{ 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};

	bool checkCell(int index)
	{
		
		return map[index];

	}

	QByteArray handle(QByteArray array)
	{
		QJsonDocument document = QJsonDocument::fromJson(array);
		auto obj = document.object();
		for(auto i : obj)
		qDebug() << "json" <<i;
		return array;

	}
};

