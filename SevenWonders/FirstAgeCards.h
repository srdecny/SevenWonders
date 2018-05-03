#pragma once
#include "Cards.h"
#include "Player.h"

class LumberMill : public BaseCard 
{
public:
	void CardEffect(Player & player);
	LumberMill();
};

class WoodenWall : public BaseCard 
{
public:
	void CardEffect(Player& player);
	WoodenWall();
};

class ClayMine : public CardThatCostGold
{
public:
	void CardEffect(Player& player);
	ClayMine();
};

class Statue : public CardsThatScorePoints
{
public:
    int ScorePoints(Player& player);
    Statue();
};
