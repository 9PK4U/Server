#pragma once
#include "GameMap.h"
#include "GameContext.h"
#include "Player.h"
class Game
{
	enum class GameProcess { Active, End };
private:
	GameProcess status = GameProcess::Active;
	GameMap map;
	Player* player1;
	Player* player2;
	Player* stepPlayer;
	int indexLastStep = -1;
	int pointLastStep = -1;

public:

	Game(Player* player1, Player* player2);
	~Game();
	const Player* getStepPlayer() const;
	GameContext getContext() const;
	void step(int index);
	std::pair<Player*, Player*> getPlayers() const;

};