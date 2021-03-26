#include "GameMap.h"

GameMap::GameMap()
{
	initMap();

	/*for (size_t i = 0; i < SIZE_MAP; i++)
	{
		qDebug() << map[i];
	}*/
}
int GameMap::takeCell(unsigned int index)
{
	if (index > SIZE_MAP - 1) throw std::exception("Invalid index");
	
	int temp = map[index];
	map[index] = OPEN_POINT;
	return temp;
}
const int& GameMap::getMap() const
{
	return *map;
}
void GameMap::initMap()
{
	std::random_device rd;
	std::mt19937 randomizer(rd());
	for (size_t i = 0; i < SIZE_MAP; i++)
	{
		map[i] = randomizer() % (MAX_POINT - MIN_POINT + 1) + MIN_POINT;
	}
	for (size_t i = 0; i < COUNT_BOMBS; i++)
	{
		while (true)
		{
			int indexBomb = randomizer() % (SIZE_MAP);
			if (map[indexBomb] != BOMB_POINT)
			{
				map[indexBomb] = BOMB_POINT;
				break;
			}

		}
	}
}