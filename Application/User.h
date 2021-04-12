#pragma once
#include <string>
using std::string;
class User
{
public:
	//enum State
	//{
	//	Played,Sleep
	//};
	string getLogin() const
	{
		return login;
	}
	int getId() const
	{
		return id;
	}
	string getGeneralPoints() const
	{
		return generalPoints;
	}

	User(string login,int id) : login(login),id(id)
	{}

private:
	int id;
	string login;
	string generalPoints;
	//string mail;

};

