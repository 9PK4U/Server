#pragma once
#include <random>
#include <QDebug>

constexpr int SIZE_MAP = 16;
constexpr int COUNT_BOMBS = 4;
constexpr int MIN_POINT = 1;
constexpr int MAX_POINT = 10;
constexpr int BOMB_POINT = -1;
constexpr int OPEN_POINT = 0;
class GameMap
{
	int map[SIZE_MAP];
public:
	GameMap();
	int takeCell(unsigned int index);
	const int& getMap() const;

private:
	void initMap();
	
};