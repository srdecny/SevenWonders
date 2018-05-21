
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
	PlayerCount = { 3, 5 };
}

IronMine::IronMine()
{
	Type = CommonResource;
	ProducedResource = Iron;
	Amount = 1;
	PlayerCount = { 3, 4 };
}

LumberMill::LumberMill()
{
	Type = CommonResource;
	ProducedResource = Wood;
	Amount = 1;
	PlayerCount = { 3, 4 };
}

StoneQuarry::StoneQuarry()
{
	Type = CommonResource;
	ProducedResource = Stone;
	Amount = 1;
	PlayerCount = { 3, 5 };
}


PapyrusManufacture::PapyrusManufacture()
{
	Type = RareResource;
	ProducedResource = Paper;
	Amount = 1;
	PlayerCount = { 3, 6 };
}

Glassworks::Glassworks()
{
	Type = RareResource;
	ProducedResource = Glass;
	Amount = 1;
	PlayerCount = { 3, 6 };
}

WeavingMill::WeavingMill()
{
	Type = RareResource;
	ProducedResource = Cloth;
	Amount = 1;
	PlayerCount = { 3, 6 };
}


Forestry::Forestry()
{
	GoldCost = 1;
	ProducedResources = { Wood, Clay };
	PlayerCount = { 6 };
}

SurfaceMine::SurfaceMine()
{
	GoldCost = 1;
	ProducedResources = { Stone, Clay };
	PlayerCount = { 4 };

}

DeepMine::DeepMine()
{
	GoldCost = 1;
	ProducedResources = { Stone, Iron };
	PlayerCount = { 6 };

}

ForestCave::ForestCave()
{
	GoldCost = 1;
	ProducedResources = { Wood, Iron };
	PlayerCount = { 5 };

}

ClayMine::ClayMine()
{
	GoldCost = 1;
	ProducedResources = { Iron, Clay };
	PlayerCount = { 3 };

}

WoodedFoothills::WoodedFoothills()
{
	GoldCost = 1;
	ProducedResources = { Stone, Wood };
	PlayerCount = { 3 };
}

// MILITARY
WoodenWall::WoodenWall()
{
	Power = 1;
	CardCost.ModifyResource(Wood, 1);
	PlayerCount = { 3, 7 };
}

WatchTower::WatchTower()
{
	Power = 1;
	CardCost.ModifyResource(Clay , 1);
	PlayerCount = { 3, 4 };

}

Barracks::Barracks()
{
	Power = 1;
	CardCost.ModifyResource(Iron, 1);
	PlayerCount = { 3, 5 };

}


// GOVERNMENT
Shrine::Shrine()
{
	Points = 2;
	PlayerCount = { 3, 5 };
	ID = 111;
}

Spa::Spa()
{
	CardCost.ModifyResource(Stone, 1);
	Points = 3;
	PlayerCount = { 3, 7 };
	ID = 112;
}

PawnShop::PawnShop()
{
	Points = 3;
	PlayerCount = { 4, 7 };

}

Theatre::Theatre()
{
	Points = 2;
	PlayerCount = { 3, 6 };
	ID = 113;
}

// MERCHANT

Pub::Pub()
{
	PlayerCount = { 4, 5, 7 };

}

void Pub::CardEffect(Player& player)
{
	player.Gold += 5;
}

std::string Pub::CardInfo()
{
	return "This card gives you 5 Gold.";
}

WesternMarket::WesternMarket()
{
	PlayerCount = { 3, 7 };
	ID = 120;

}

void WesternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostRight = 1;
}

std::string WesternMarket::CardInfo()
{
	return "This card allows you to buy Common resources from your left neighbour for 1 Gold.";
}

EasternMarket::EasternMarket()
{
	PlayerCount = { 3, 7 };
	ID = 121;
}

void EasternMarket::CardEffect(Player& player)
{
	player.CommonResourceCostLeft = 1;
}

std::string EasternMarket::CardInfo()
{
	return "This card allows you to buy Common resources from your right neighbour for 1 Gold.";
}

Marketplace::Marketplace()
{
	PlayerCount = { 3, 6 };
	ID = 122;
}

void Marketplace::CardEffect(Player& player)
{
	player.RareResourceCost = 1;
}

std::string Marketplace::CardInfo()
{
	return "This card allows you to buy Rare resources from both neighbours for 1 Gold.";
}

// SCIENCE

ScriberShop::ScriberShop()
{
	CardCost.ModifyResource(Paper, 1);
	Symbol = Cog;
	PlayerCount = { 3, 4 };
	ID = 100;
}

Aphotecary::Aphotecary()
{
	CardCost.ModifyResource(Cloth, 1);
	Symbol = Compass;
	PlayerCount = { 3, 5 };
	ID = 101;

}

Workshop::Workshop()
{
	CardCost.ModifyResource(Glass, 1);
	Symbol = Tableau;
	PlayerCount = { 3, 7 };
	ID = 102;
}

