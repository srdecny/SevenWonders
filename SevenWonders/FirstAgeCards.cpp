
#include "FirstAgeCards.h"
#include <vector>
#include <iostream>


// RESOURCES
LumberMill::LumberMill()
{
	CardName = "Lumber Mill";
	PlayerCount = { 3, 4 };
	type = CommonResource;
	ID = 1;
}

void LumberMill::CardEffect(Player& player)
{
	player.ModifyTradableResources(Wood, 1);
}

IronMine::IronMine()
{
	CardName = "Lumber Mill";
	PlayerCount = { 3, 4 };
	type = CommonResource;
	ID = 2;
}

void IronMine::CardEffect(Player& player)
{
	player.ModifyTradableResources(Iron, 1);
}

StoneQuarry::StoneQuarry()
{
	CardName = "Stone Quarry";
	PlayerCount = { 3, 5 };
	type = CommonResource;
	ID = 3;
}

void StoneQuarry::CardEffect(Player& player)
{
	player.ModifyTradableResources(Stone, 1);
}

ClayDeposit::ClayDeposit()
{
	CardName = "Clay Deposit";
	PlayerCount = { 3, 5 };
	type = CommonResource;
	ID = 4;
}

void ClayDeposit::CardEffect(Player& player)
{
	player.ModifyTradableResources(Clay, 1);
}

// DUAL RESOURCES
ClayMine::ClayMine()
{
	CardName = "Clay Mine";
	PlayerCount = { 3 };
	GoldCost = 1;
	type = CommonResource;
	ID = 12;
}

void ClayMine::CardEffect(Player & player)
{
	player.Gold -= 1;
	// make all new permutations avaliable with the dual resources
    // can use only one of the two resources at one time
	std::vector<ResourceVector> originalResources = player.TradableResources;
	for (ResourceVector &vector : originalResources) { vector.ModifyResource(Clay, 1); }
	for (ResourceVector &vector : player.TradableResources) { vector.ModifyResource(Iron, 1); }
	for (ResourceVector &vector : originalResources) { player.TradableResources.push_back(vector); }
}

// MILITARY
WatchTower::WatchTower()
{
	CardName = "Watch Tower";
	CardCost.ModifyResource(Clay, 1);
	type = Military;
	PlayerCount = { 3, 4 };
	ID = 11;
}

void WatchTower::CardEffect(Player & player)
{
	player.MilitaryPoints++;
}

Barracks::Barracks()
{
	CardName = "Barracks";
	CardCost.ModifyResource(Wood, 1);
	type = Military;
	PlayerCount = { 3, 5 };
	ID = 12;
}

void Barracks::CardEffect(Player & player)
{
	player.MilitaryPoints++;
}

WoodenWall::WoodenWall()
{
	CardName = "Wooden Wall";
	CardCost.ModifyResource(Wood, 1);
	type = Military;
	PlayerCount = { 3, 7 };
	ID = 13;
}

void WoodenWall::CardEffect(Player & player)
{
	player.MilitaryPoints += 1;
}

// MERCHANTS
Marketplace::Marketplace()
{
	CardName = "Marketplace";
	type = Merchant;
	PlayerCount = { 3, 6 };
	ID = 14;
}

void Marketplace::CardEffect(Player& player)
{
	player.RareResourceCost = 1;
}

EasternMarket::EasternMarket()
{
	CardName = "Eastern Market";
	type = Merchant;
	PlayerCount = { 3, 7 };
	ID = 15;
}

void EasternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostRight = 1;
}

WesternMarket::WesternMarket()
{
	CardName = "Western Market";
	type = Merchant;
	PlayerCount = { 3, 7 };
	ID = 16;
}

void WesternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostLeft = 1;
}

Pub::Pub()
{
	CardName = "Pub";
	type = Merchant;
	PlayerCount = { 4, 5, 7 };
	ID = 17;
}

void Pub::CardEffect(Player& player)
{
	player.Gold += 5;
}

// GOVERNMENT

Shrine::Shrine()
{
	CardName = "Shrine";
	type = Government;
	PlayerCount = { 3, 5 };
	ID = 18;
}

int Shrine::ScorePoints(Player &player)
{
	return 2;
}

PawnShop::PawnShop()
{
	CardName = "Pawn Shop";
	type = Government;
	PlayerCount = { 4, 7 };
	ID = 19;
}

int PawnShop::ScorePoints(Player &player)
{
	return 3;
}

Spa::Spa()
{
	CardName = "Spa";
	CardCost.ModifyResource(Stone, 1);
	type = Government;
	PlayerCount = { 3, 7 };
	ID = 20;
}

int Spa::ScorePoints(Player &player)
{
	return 3;
}

Theatre::Theatre()
{
	CardName = "Theatre";
	CardCost.ModifyResource(Stone, 1);
	type = Government;
	PlayerCount = { 3, 6 };
	ID = 21;
}

int Theatre::ScorePoints(Player &player)
{
	return 2;
}

// SCIENCE

ScribeShop::ScribeShop()
{
	CardName = "Scribe Shop";
	CardCost.ModifyResource(Glass, 1);
	type = Science;
	PlayerCount = { 3, 4 };
	ID = 22;
}

void ScribeShop::CardEffect(Player &player)
{
	player.ModifyScienceVectors(Tableau, 1);
}

Workshop::Workshop()
{
	CardName = "Workshop";
	CardCost.ModifyResource(Glass, 1);
	type = Science;
	PlayerCount = { 3, 5 };
	ID = 23;
}

void Workshop::CardEffect(Player &player)
{
	player.ModifyScienceVectors(Cog, 1);
}

Aphotecary::Aphotecary()
{
	CardName = "Workshop";
	CardCost.ModifyResource(Cloth, 1);
	type = Science;
	PlayerCount = { 3, 5 };
	ID = 24;
}

void Aphotecary::CardEffect(Player &player)
{
	player.ModifyScienceVectors(Compass, 1);
}