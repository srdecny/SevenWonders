#include "stdafx.h"
#include "Wonders.hpp"
#include "SecondAgeCards.h"
#include "ThirdAgeCards.h"
#include "Player.h"



void BaseWonder::InitialResource(Player& player)
{
	player.ModifyTradableResources(StartingResource, 1);
}

void BaseWonder::GetNextWonderBuilding()
{
	if (CurrentLevel >= (int)WonderBuildings.capacity() - 1) CurrentBuilding = nullptr;
	else
	{
		CurrentLevel++;
		CurrentBuilding = WonderBuildings[CurrentLevel];
	}

}



BaseFirstStage::BaseFirstStage()
{
	Points = 3;
}

std::string BaseFirstStage::CardInfo()
{
	return "This Wonder stage gives you " + std::to_string(Points) + " Victory points.";
}

BaseThirdStage::BaseThirdStage()
{
	Points = 7;
}

std::string BaseThirdStage::CardInfo()
{
	return "This Wonder stage gives you " + std::to_string(Points) + " Victory points.";
}


Gizah::Gizah()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared<GizahSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Stone, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Stone, 4);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Stone;
	WonderName = "Great Pyramid of Giza";
}

GizahSecondStage::GizahSecondStage()
{
	CardCost.ModifyResource(Stone, 2);
	Points = 5;
}

std::string GizahSecondStage::CardInfo()
{
	return "This Wonder stage gives you 5 Victory points.";
}


Rhodos::Rhodos()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared<RhodosSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Wood, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Iron, 4);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Iron;
	WonderName = "Colossus of Rhodes";
}

RhodosSecondStage::RhodosSecondStage()
{
	CardCost.ModifyResource(Clay, 3);
}

void RhodosSecondStage::CardEffect(Player& player)
{
	player.MilitaryPoints += 2;
}

std::string RhodosSecondStage::CardInfo()
{
	return "This Wonder stage gives you 2 Military points.";
}


Alexandria::Alexandria()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared <AlexandriaSecondStage> ());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Stone, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Glass, 4);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Glass;

	WonderName = "Library of Alexandria";
}

AlexandriaSecondStage::AlexandriaSecondStage()
{
	CardCost.ModifyResource(Iron, 2);
}

std::string AlexandriaSecondStage::CardInfo()
{
	return "This Wonder stage gives you any single Common resource at a given time.";
}

void AlexandriaSecondStage::CardEffect(Player& player)
{
	Caravanserai DummyBuilding;
	DummyBuilding.CardEffect(player);
}


Babylon::Babylon()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared <BabylonSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Clay, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Clay, 4);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Clay;

	WonderName = "Hanging Gardens of Babylon";
}

BabylonSecondStage::BabylonSecondStage()
{
	CardCost.ModifyResource(Wood, 3);
}

void BabylonSecondStage::CardEffect(Player& player)
{
	ResearchersGuild DummyBuilding;
	DummyBuilding.CardEffect(player);
}

std::string BabylonSecondStage::CardInfo()
{
	return "This Wonder stage provides any one Research symbol at a given time.";
}


Ephesus::Ephesus()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared <EphesusSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Stone, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Paper, 2);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Paper;

	WonderName = "Hanging Gardens of Babylon";
}

EphesusSecondStage::EphesusSecondStage()
{
	CardCost.ModifyResource(Wood, 2);
}

void EphesusSecondStage::CardEffect(Player& player)
{
	player.Gold += 9;
}

std::string EphesusSecondStage::CardInfo()
{
	return "This Wonder stage gives you 9 gold.";
}


Olympia::Olympia()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared <OlympiaSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Wood, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Iron, 2);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Wood;

	WonderName = "Statue of Zeus at Olympia";
}

OlympiaSecondStage::OlympiaSecondStage()
{
	CardCost.ModifyResource(Stone, 2);
}

void OlympiaSecondStage::CardEffect(Player& player)
{
	Tribunal DummyBuilding;
	DummyBuilding.CardEffect(player);
}

std::string OlympiaSecondStage::CardInfo()
{
	return "This Wonder stage gives you any single Rare resource at a given time";
}


Halikarnassos::Halikarnassos()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared <HalikarnassosSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Clay, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Cloth, 2);

	CurrentBuilding = WonderBuildings[0];
	StartingResource = Cloth;

	WonderName = "Mausoleum at Halicarnassus";
}

HalikarnassosSecondStage::HalikarnassosSecondStage()
{
	CardCost.ModifyResource(Iron, 3);
}

void HalikarnassosSecondStage::CardEffect(Player& player)
{
	GamersGuild DummyBuilding;
	DummyBuilding.CardEffect(player);
}

std::string HalikarnassosSecondStage::CardInfo()
{
	return "This Wonder stage gives you 1 Victory point for every 3 gold you have at the end of the game.";
}

