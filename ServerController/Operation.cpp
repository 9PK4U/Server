#include "Operation.h"

Operation::Operation(Type type, Parametrs parametrs) : type(type), parametrs(parametrs)
{
}

Operation::Type Operation::getType() const
{
    return type;
}

Parametrs Operation::getParametrs() const
{
    return 	parametrs;
}

string Operation::getParametr(string key) const
{
    return parametrs.at(key);
}
string Operation::operator[](string key) const
{
    return getParametr(key);
}

string Operation::typeToString(Type type)
{
    string sType;
    switch (type)
    {
    case Operation::Type::Autorization:
        sType = "Autorization";
        break;
    case Operation::Type::Registration:
        sType = "Registration";
        break;
    case Operation::Type::EnterCell:
        sType = "EnterCell";
        break;
    case Operation::Type::GetStatistic:
        sType = "GetStatistic";
        break;
    case Operation::Type::FindGame:
        sType = "FindGame";
        break;
    case Operation::Type::EndGame:
        sType = "EndGame";
        break;
    case Operation::Type::StatusGame:
        sType = "StatusGame";
        break;
    case Operation::Type::Error:
        sType = "Error";
        break;
    default:
        break;
    }
    return sType;
}

Operation::Type Operation::stringToType(string sType)
{
    Type type;
    if (sType == "Autorization")
        return Type::Autorization;
    if (sType == "EndGame")
        return Type::EndGame;
    if (sType == "EnterCell")
        return Type::EnterCell;
    if (sType == "Error")
        return Type::Error;
    if (sType == "FindGame")
        return Type::FindGame;
    if (sType == "GetStatistic")
        return Type::GetStatistic;
    if (sType == "Registration")
        return Type::Registration;
    if (sType == "StatusGame")
        return Type::StatusGame;
    throw std::exception("Incorrect Type");

}


