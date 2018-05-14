#pragma once
#include "Cards.h"
#include "Player.h"

// MILITARY
class WoodenWall : public BaseCard 
{
public:
	void CardEffect(Player& player);
	WoodenWall();
};

class WatchTower : public BaseCard
{
	void CardEffect(Player& player);
	WatchTower();
};

class Barracks : public BaseCard
{
	void CardEffect(Player& player);
	Barracks();
};

// RESOURCES

class ClayMine : public CardThatCostGold
{
public:
	void CardEffect(Player& player);
	ClayMine();
};

class LumberMill : public BaseCard
{
public:
	void CardEffect(Player & player);
	LumberMill();
};

class IronMine : public BaseCard
{
public:
	void CardEffect(Player & player);
	IronMine();
};

class StoneQuarry : public BaseCard
{
public:
	void CardEffect(Player & player);
	StoneQuarry();
};

class ClayDeposit : public BaseCard
{
public:
	void CardEffect(Player & player);
	ClayDeposit();
};

// MERCHANTS
class Marketplace : public BaseCard
{
	void CardEffect(Player& player);
	Marketplace();
};

class WesternMarket : public BaseCard
{
	void CardEffect(Player& player);
	WesternMarket();
};

class EasternMarket : public BaseCard
{
	void CardEffect(Player& player);
	EasternMarket();
};

class Pub : public BaseCard
{
	void CardEffect(Player& player);
	Pub();
};

// GOVERNMENT
class Shrine : public BaseCard
{
public: // hack, no idea why it's needed
	int ScorePoints(Player& player);
	Shrine();
};

class PawnShop : public BaseCard
{
	int ScorePoints(Player& player);
	PawnShop();
};

class Theatre : public BaseCard
{
	int ScorePoints(Player& player);
	Theatre();
};

class Spa : public BaseCard
{
	int ScorePoints(Player& player);
	Spa();
};

// SCIENCE
class ScribeShop : public BaseCard
{
	void CardEffect(Player& player);
	ScribeShop();
};

class Workshop : public BaseCard
{
	void CardEffect(Player& player);
	Workshop();
};

class Aphotecary : public BaseCard
{
	void CardEffect(Player& player);
	Aphotecary();
};

