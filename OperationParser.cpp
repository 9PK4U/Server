#include "OperationParser.h"

Operation OperationParser::JsonToOperation(QJsonDocument document)
{
    Parametrs params;
	auto obj = document.object();
	for (auto i : obj)
	{
		if (i == "Parametrs")
			if (i.isArray())
			{
				//auto paramsObj = i.toObject();
				//for (auto it : paramsObj)
				//{
				//	params.insert("kek", "kek");
				//}
			}
		qDebug() << "json" << i;
	}


    return Operation(Operation::Type::Autorization,params);
}
