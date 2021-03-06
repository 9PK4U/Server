#include "OperationParser.h"


Operation OperationParser::JsonToOperation(QJsonDocument document)
{
    Parametrs params;
	auto obj = document.object();
	if (!validKeys(obj.keys()))
	{
		throw std::exception("Error keys");
	}
	if (!validParametrs(obj["Parametrs"]))
	{
		throw std::exception("Error Parametrs");
	}
	auto paramsObj = obj["Parametrs"].toObject();
	for (auto i : paramsObj.keys())
	{
		params[i.toStdString()] = paramsObj[i].toString().toStdString();
	}

	try
	{
		return Operation(getType(obj["Operation"]), params);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

QByteArray OperationParser::OperationToJson(Operation operation)
{
	QJsonObject obj;
	QJsonObject params;



	for (auto i : operation.getParametrs())
	{
		params.insert(QString::fromStdString(i.first), QString::fromStdString(i.second));
	}
	obj["Operation"] = QString::fromStdString(Operation::typeToString(operation.getType()));
	obj["Parametrs"] = params;

	QJsonDocument doc(obj);
	return doc.toJson(QJsonDocument::JsonFormat::Compact);
}

bool OperationParser::validKeys(QStringList& keys)
{
	if (keys.isEmpty())
		return false;
	if(keys.indexOf("Parametrs") == -1) return false;
	if(keys.indexOf("Operation") == -1) return false;
	return true;
}
bool OperationParser::validParametrs(QJsonValueRef& parametrs)
{
	if (!parametrs.isObject())
		return false;


	for (auto& i : parametrs.toObject())
	{
		if (! i.isString())
			return false;

		/*if (i.toObject().keys().size() != 1)
			return false;*/

		//for (auto& it : i.toObject())
		//{
		//	auto a = it.type();
		//	if(a != QJsonValue::Type::String)
		//		return false;
		//}
	}
	
	return true;
}

Operation::Type OperationParser::getType(QJsonValueRef& operation)
{
	if (!operation.isString()) throw std::exception("Operation is not string value");
	try
	{
		return Operation::stringToType(operation.toString().toStdString());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
	
}
