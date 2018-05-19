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

	mill->Play(engine.Players[1]);
	engine.Players[0].Gold = 3;
    
	vector<shared_ptr<BaseCard>> vector;
	vector.push_back(mine);
	vector.push_back(forestry);
	vector.push_back(wall);
	vector.push_back(mill);
	vector.push_back(statue);
	vector.push_back(workshop);


	engine.PlayersHands[0] = vector;
	engine.ProcessSingleTurn();
	
	engine.PrintPlayerStats(cout, engine.Players[0] );
	cout << engine.ScorePlayerPoints(engine.Players[0]);
	

	getchar();
}

