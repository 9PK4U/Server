#pragma once
#include <string>
using std::string;
class User
{
private:
	string login;
	string generalPoints;
	//string mail;

public:
	string getLogin() const
	{
		return login;
	}
	string getGeneralPoints() const
	{
		return generalPoints;
	}

	User(string login) : login(login)
	{}
};

