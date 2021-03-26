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

