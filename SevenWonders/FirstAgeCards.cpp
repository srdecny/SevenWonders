
#include "Cards.h"
#include <vector>
#include <iostream>
#include "FirstAgeCards.h"

// RESOURCES
ClayDeposit::ClayDeposit() 
{
	Type = CommonResource;
	ProducedResource = Clay;
	Amount = 1;
}

IronMine::IronMine()
{
	Type = CommonResource;
	ProducedResource = Iron;
	Amount = 1;
}

LumberMill::LumberMill()
{
	Type = CommonResource;
	ProducedResource = Wood;
	Amount = 1;
}

StoneQuarry::StoneQuarry()
{
	Type = CommonResource;
	ProducedResource = Stone;
	Amount = 1;
}


PapyrusManufacture::PapyrusManufacture()
{
	Type = RareResource;
	ProducedResource = Paper;
	Amount = 1;
}

Glassworks::Glassworks()
{
	Type = RareResource;
	ProducedResource = Glass;
	Amount = 1;
}

WeavingMill::WeavingMill()
{
	Type = RareResource;
	ProducedResource = Cloth;
	Amount = 1;
}


Forestry::Forestry()
{
	GoldCost = 1;
	ProducedResources = { Wood, Clay };
}

SurfaceMine::SurfaceMine()
{
	GoldCost = 1;
	ProducedResources = { Stone, Clay };
}

DeepMine::DeepMine()
{
	GoldCost = 1;
	ProducedResources = { Stone, Iron };
}

ForestCave::ForestCave()
{
	GoldCost = 1;
	ProducedResources = { Wood, Iron };
}

ClayMine::ClayMine()
{
	GoldCost = 1;
	ProducedResources = { Iron, Clay };
}

WoodedFoothills::WoodedFoothills()
{
	GoldCost = 1;
	ProducedResources = { Stone, Wood };
}

// MILITARY
WoodenWall::WoodenWall()
{
	Power = 1;
	CardCost.ModifyResource(Wood, 1);
}

WatchTower::WatchTower()
{
	Power = 1;
	CardCost.ModifyResource(Clay , 1);
}

Barracks::Barracks()
{
	Power = 1;
	CardCost.ModifyResource(Iron, 1);
}


// GOVERNMENT
Shrine::Shrine()
{
	Points = 2;
}

Spa::Spa()
{
	CardCost.ModifyResource(Stone, 1);
	Points = 3;
}

PawnShop::PawnShop()
{
	Points = 3;
}

Theatre::Theatre()
{
	Points = 2;
}

// MERCHANT

Pub::Pub()
{

}

void Pub::CardEffect(Player& player)
{
	player.Gold += 5;
}

WesternMarket::WesternMarket()
{

}

void WesternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostRight = 1;
}

EasternMarket::EasternMarket()
{

}

void EasternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostLeft = 1;
}

Marketplace::Marketplace()
{

}

void Marketplace::CardEffect(Player& player)
{
	player.RareResourceCost = 1;
}

// SCIENCE

ScriberShop::ScriberShop()
{
	CardCost.ModifyResource(Paper, 1);
	Symbol = Cog;
}

Aphotecary::Aphotecary()
{
	CardCost.ModifyResource(Cloth, 1);
	Symbol = Compass;
}

Workshop::Workshop()
{
	CardCost.ModifyResource(Glass, 1);
	Symbol = Tableau;
}