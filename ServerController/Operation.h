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

									
	static string typeToString(Type type);
	static Type stringToType(string type);


	std::string toString()
	{
		string str;
		str+= std::string("Type: ") + Operation::typeToString(getType()) + string("   Parametrs: {");
		for (auto i : getParametrs())
			str += std::string("Key:") + i.first + std::string("   Value:") + i.second + std::string(",");
		str += "}";
		return str;
	}


};

