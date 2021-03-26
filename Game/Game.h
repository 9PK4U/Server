#pragma once
#include "GameMap.h"
#include "GameContext.h"
#include "Player.h"
class Game
{
	enum class GameProcess { Active, End };
private:
	GameMap map;
	Player* player1;
	Player* player2;
	Player* stepPlayer;
	int indexLastStep;
	int pointLastStep;

public:

	Game(Player* player1, Player* player2);
	const Player* getStepPlayer() const;
	GameContext getContext();
	GameProcess step(int index);
};