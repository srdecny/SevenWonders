// Wonders.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

int main()
{

	GameEngine engine;
	engine.InitializeTheGame(3);

	auto mine = make_shared<IronMine>();
	auto forestry = make_shared<Forestry>();
    auto wall = make_shared<WoodenWall>();
	auto mill = make_shared<LumberMill>();
    auto statue = make_shared<Shrine>();
	auto workshop = make_shared<Workshop>();
    
	/*
	mine->Play(engine.Players[1]);
    mill->Play(engine.Players[1]);
    statue->Play(engine.Players[1]);
	forestry->Play(engine.Players[1]);
	workshop->Play(engine.Players[1]);
	*/
	vector<shared_ptr<BaseCard>> vector { wall, mine };
	engine.PresentCardsToPlayer(std::cout, engine.Players[0], vector);
    cout << "Player has scored: " << engine.ScorePlayerPoints(engine.Players[1]) << endl;
	engine.PrintPlayerStats(cout, engine.Players[1] );

	getchar();
}

