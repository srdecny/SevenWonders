#pragma once
#include "SecondAgeCards.h"

// RESOURCES

ClayFactory::ClayFactory()
{
	ProducedResource = Clay;
	Amount = 2;
	GoldCost = 1;
	PlayerCount = { 3, 4 };
}

StoneFactory::StoneFactory()
{
	ProducedResource = Stone;
	Amount = 2;
	GoldCost = 1;
	PlayerCount = { 3, 4 };
}

IronFactory::IronFactory()
{
	ProducedResource = Iron;
	Amount = 2;
	GoldCost = 1;
	PlayerCount = { 3, 4 };
}

WoodFactory::WoodFactory()
{
	ProducedResource = Wood;
	Amount = 2;
	GoldCost = 1;
	PlayerCount = { 3, 4 };
}


SecondPapyrusManufacture::SecondPapyrusManufacture()
{
	Type = RareResource;
	ProducedResource = Paper;
	Amount = 1;
	PlayerCount = { 3, 5 };
}

SecondGlassworks::SecondGlassworks()
{
	Type = RareResource;
	ProducedResource = Glass;
	Amount = 1;
	PlayerCount = { 3, 5 };
}

SecondWeavingMill::SecondWeavingMill()
{
	Type = RareResource;
	ProducedResource = Cloth;
	Amount = 1;
	PlayerCount = { 3, 5 };
}


// MILITARY

StoneWall::StoneWall()
{
	Power = 2;
	CardCost.ModifyResource(Stone, 3);
	PlayerCount = { 3, 7 };
}

Archery::Archery()
{
	Power = 2;
	CardCost.ModifyResource(Wood, 2);
	CardCost.ModifyResource(Iron, 1);
	PrerequisiteCards.push_back(102); // Workshop
	PlayerCount = { 3, 6 };

}

Stables::Stables()
{
	Power = 2;
	CardCost.ModifyResource(Clay, 1);
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Iron, 1);
	PrerequisiteCards.push_back(101); // Aphotecary
	PlayerCount = { 3, 5 };
}

TrainingGrounds::TrainingGrounds()
{
	Power = 2;
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Wood, 1);
	PlayerCount = { 4, 6, 7};
}

// GOVERNMENT

Statue::Statue()
{
	Points = 4;
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Wood, 1);
	PrerequisiteCards.push_back(113); // Theatre
	PlayerCount = { 3, 7 };
}

Aqueduct::Aqueduct()
{
	Points = 5;
	CardCost.ModifyResource(Stone, 3);
	PrerequisiteCards.push_back(112); // Spa
	PlayerCount = { 3, 7 };
}

Temple::Temple()
{
	Points = 3;
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Clay, 1);
	CardCost.ModifyResource(Glass, 1);
	PrerequisiteCards.push_back(111); // Shrine
	PlayerCount = { 3, 6 };
}

CourtHouse::CourtHouse()
{
	Points = 4;
	CardCost.ModifyResource(Clay, 2);
	CardCost.ModifyResource(Cloth, 1);
	PrerequisiteCards.push_back(100); // ScriberShop
	PlayerCount = { 3, 5 };
}

// MERCHANT

Caravanserai::Caravanserai()
{
	CardCost.ModifyResource(Wood, 2);
	PrerequisiteCards.push_back(122); // Marketplace
	PlayerCount = { 3, 5, 6 };
}

void Caravanserai::CardEffect(Player& player)
{
	MultipleResourceBuilding DummyBuilding;
	DummyBuilding.ProducedResources = { Wood, Clay, Iron, Stone };
	DummyBuilding.CardEffect(player);
}

std::string Caravanserai::CardInfo()
{
	return "This card produces any single Common resource at a given time.";
}

Tribunal::Tribunal()
{
	CardCost.ModifyResource(Clay, 2);
	PrerequisiteCards.push_back(120); // Eastern Market
	PrerequisiteCards.push_back(121); // Western Market
	PlayerCount = { 3, 6, 7 };
}

void Tribunal::CardEffect(Player& player)
{
	MultipleResourceBuilding DummyBuilding;
	DummyBuilding.ProducedResources = { Glass, Cloth, Paper };
	DummyBuilding.CardEffect(player);

}

std::string Tribunal::CardInfo()
{
	return "This card produces any single Rare resource at a given time.";
}

Vineyard::Vineyard()
{
	PlayerCount = { 3, 6 };
}

void Vineyard::CardEffect(Player& player)
{
	int ResourceCards = 0;

}

std::string Vineyard::CardInfo()
{
	return "This card gives you 1 Gold for every single Common resource card you and your neighbours have.";
}

Bazaar::Bazaar()
{
	PlayerCount = { 4, 7 };
}

void Bazaar::CardEffect(Player& player)
{

}

std::string Bazaar::CardInfo()
{
	return "This card gives you 2 Gold for every single Rare resource card you and your neighbours have.";
}