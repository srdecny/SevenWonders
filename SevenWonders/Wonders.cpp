#include "Wonders.hpp"
#include "Player.h"

BaseWonder::BaseWonder()
{
    return;
}
BaseWonder::~BaseWonder()
{
    return;
}

Gizah::Gizah()
{
	WonderLevel = 3;
	WonderBuildings = { Pyramides1(), Pyramides2(), Pyramides3() };
}

void Gizah::InitialResource(Player &player)
{
    player.ModifyTradableResources(Stone, 1);
}

Pyramides1::Pyramides1()
{
    CardCost.ModifyResource(Stone, 2);
}

int Pyramides1::ScorePoints(Player& player)
{
    return 3;
}

Pyramides2::Pyramides2()
{
    CardCost.ModifyResource(Wood, 3);
}

int Pyramides2::ScorePoints(Player& player)
{
    return 5;
};

Pyramides3::Pyramides3()
{
    CardCost.ModifyResource(Stone, 4);
}

int Pyramides3::ScorePoints(Player &)
{
    return 7;
};


Rhodos::Rhodos()
{
	WonderLevel = 3;
	WonderBuildings = { Rhodos1(), Rhodos2(), Rhodos3() };
}

void Rhodos::InitialResource(Player& player)
{
	player.ModifyTradableResources(Iron, 1);
}

Rhodos1::Rhodos1()
{
	CardCost.ModifyResource(Wood, 2);
}

int Rhodos1::ScorePoints(Player& player)
{
	return 3;
}

Rhodos2::Rhodos2()
{
	CardCost.ModifyResource(Clay, 3);
}

void Rhodos2::CardEffect(Player& player)
{
	player.MilitaryPoints += 2;
}

Rhodos3::Rhodos3()
{
	CardCost.ModifyResource(Iron, 4);
}

int Rhodos3::ScorePoints(Player& player)
{
	return 7;
}