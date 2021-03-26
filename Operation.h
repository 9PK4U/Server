#pragma once
#include <map>
#include <string>

using std::map;
using std::string;

using Parametrs = map<string, string>;
class Operation
{
public:
	enum class Sender {Client, Server};
	enum class Type {
		Autorization,
		Registration,
		EnterCell,
		GetStatistic,
		FindGame,
		EndGame,
		StatusGame,
		Error
	};

	Operation(Type type, Parametrs parametrs);

private:
	Type type;
	Parametrs parametrs;

public:
	Type getType() const;
	Parametrs getParametrs() const;
	string getParametr(string key) const;

	string operator[](string key) const;

									

};

