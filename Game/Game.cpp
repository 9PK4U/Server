#include "Game.h"

Game::Game(Player* player1, Player* player2) : player1(player1), player2(player2)
{
    stepPlayer = player1;
    player1->points = 0;
    player2->points = 0;
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete stepPlayer;
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

void Game::step(int index)
{
    indexLastStep = index;
    pointLastStep = map.takeCell(index);
    

    if (pointLastStep == BOMB_POINT)
    {
        stepPlayer->alive = false;
    }
    else
    {
        stepPlayer->points += pointLastStep;
    }
    if (player1->alive || player2->alive)
    {
        status = GameProcess::Active;

        if (!player1->alive)
        {
            stepPlayer = player2;
        }
        else if (!player2->alive)
        {
            stepPlayer = player1;
        }
        else
        {
            stepPlayer = stepPlayer == player1 ? player2 : player1;
        }
        
    }
    else
    {
        status = GameProcess::End;
    }
    
}

std::pair<Player*, Player*> Game::getPlayers() const
{
    return std::pair<Player*, Player*>(player1,player2);
}
