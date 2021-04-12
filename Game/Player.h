#pragma once

#include <string>
using std::string;
struct Player
{
	string name;
	int points;
	int id;
	bool alive = true;

	Player(string name, int id) : name(name), id(id)
	{
		points = 0;
	}

};