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

GameContext Game::getContext() const
{
    string strMap;
    for (int i = 0; i < SIZE_MAP; i++)
    {
        strMap += std::to_string((&map.getMap())[i]) +" ";
    }
    GameContext context;
    context.currentStepPlayerName = stepPlayer->name;
    context.lastIndexCell = std::to_string(indexLastStep);
    context.lastPoint = std::to_string(pointLastStep);
    context.map = strMap;
    context.player1Name = player1->name;
    context.player1Points = std::to_string(player1->points);
    context.player2Name = player2->name;
    context.player2Points = std::to_string(player2->points);
    context.statusGame = status==GameProcess::Active?"Active":"End";

    return context;
}

Game::GameProcess Game::step(int index)
{
    indexLastStep = index;
    pointLastStep = map.takeCell(index);
    stepPlayer->points += pointLastStep;

    stepPlayer = stepPlayer == player1 ? player2 : player1;
    return GameProcess::Active; //???????????
}

std::pair<string, string> Game::getNamesPlayers() const
{
    return std::pair<string, string>(player1->name,player2->name);
}
