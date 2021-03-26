#pragma once

#include <string>
using std::string;
struct Player
{
	string name;
	int points;

	Player(string name) : name(name)
	{
		points = 0;
	}
};
