#include "Wonders.hpp"
#include "Player.h"

BaseWonder::BaseWonder()
{
}
BaseWonder::~BaseWonder()
{
    return;
}

void BaseWonder::GetNextWonderBuilding()
{
	if (CurrentLevel >= (int)WonderBuildings.capacity()) CurrentBuilding = nullptr;
	else
	{
		CurrentLevel++;
		CurrentBuilding = WonderBuildings[CurrentLevel];
	}

}

Gizah::Gizah()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared<GizahSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Stone, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Stone, 4);

	CurrentBuilding = WonderBuildings[0];

	WonderName = "Pyramides of Gizah";
}

void Gizah::InitialResource(Player &player)
{
    player.ModifyTradableResources(Stone, 1);
}


Rhodos::Rhodos()
{
	WonderBuildings.push_back(std::make_shared<BaseFirstStage>());
	WonderBuildings.push_back(std::make_shared<RhodosSecondStage>());
	WonderBuildings.push_back(std::make_shared<BaseThirdStage>());

	WonderBuildings[0]->CardCost.ModifyResource(Wood, 2);
	WonderBuildings[2]->CardCost.ModifyResource(Iron, 4);

	CurrentBuilding = WonderBuildings[0];

	WonderName = "Colossus of Rhodos";
}

void Rhodos::InitialResource(Player& player)
{
	player.ModifyTradableResources(Iron, 1);
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


GizahSecondStage::GizahSecondStage()
{
	CardCost.ModifyResource(Stone, 2);
	Points = 5;
}

std::string GizahSecondStage::CardInfo()
{
	return "This Wonder stage gives you 5 Victory points.";
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