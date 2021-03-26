#include "Game.h"

Game::Game(Player* player1, Player* player2) : player1(player1), player2(player2)
{
    stepPlayer = player1;
    player1->points = 0;
    player2->points = 0;
}

const Player* Game::getStepPlayer() const
{
    return stepPlayer;
}

GameContext Game::getContext()
{
    string strMap;
    for (int i = 0; i < SIZE_MAP; i++)
    {
        strMap += std::to_string((&map.getMap())[i]) +" ";
    }
    return GameContext(
        {
            player1->name,
            player2->name,
            strMap,
            stepPlayer->name,std::to_string(player1->points),
            std::to_string(player2->points),
            std::to_string(indexLastStep),
            std::to_string(pointLastStep) 
        });
}

Game::GameProcess Game::step(int index)
{
    indexLastStep = index;
    pointLastStep = map.takeCell(index);
    stepPlayer->points += pointLastStep;

    stepPlayer = stepPlayer == player1 ? player2 : player1;
    return GameProcess::Active; //???????????
}
