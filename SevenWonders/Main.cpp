// Wonders.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"
#include "FirstAgeCards.h"

using namespace std;

int main()
{

	GameEngine engine;
	engine.InitializeTheGame(3);

    auto mine = make_shared<ClayMine>();
    auto wall = make_shared<WoodenWall>();
    auto mill = make_shared<LumberMill>();
    auto statue = make_shared<Statue>();
    
	mine->Play(engine.Players[1]);
    mill->Play(engine.Players[1]);
    statue->Play(engine.Players[1]);

	vector<shared_ptr<BaseCard>> vector { wall, mine };
	engine.PresentCardsToPlayer(std::cout, engine.Players[0], vector);
    cout << "Player has scored: " << engine.ScorePlayerPoints(engine.Players[1]) << endl;
		

	getchar();
}

