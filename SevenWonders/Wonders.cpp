#include "Wonders.hpp"
#include "Player.h"

BaseWonder::BaseWonder()
{
	GetNextWonderBuilding();
}
BaseWonder::~BaseWonder()
{
    return;
}

void BaseWonder::GetNextWonderBuilding()
{
	if (WonderLevel == WonderBuildings.capacity()) CurrentBuilding = nullptr;
	else CurrentBuilding = std::make_shared<BaseCard>(WonderBuildings[WonderLevel]);
}

Gizah::Gizah()
{
	WonderLevel = 3;
	WonderBuildings = { BaseFirstStage(), GizahSecondStage(), BaseThirdStage() };
	WonderBuildings[0].CardCost.ModifyResource(Stone, 2);
	WonderBuildings[2].CardCost.ModifyResource(Stone, 4);
}

void Gizah::InitialResource(Player &player)
{
    player.ModifyTradableResources(Stone, 1);
}


Rhodos::Rhodos()
{
	WonderLevel = 3;
	WonderBuildings = { BaseFirstStage(), RhodosSecondStage(), BaseThirdStage() };
	WonderBuildings[0].CardCost.ModifyResource(Wood, 2);
	WonderBuildings[2].CardCost.ModifyResource(Iron, 4);
}

void Rhodos::InitialResource(Player& player)
{
	player.ModifyTradableResources(Iron, 1);
}


BaseFirstStage::BaseFirstStage()
{
	Points = 3;
}

BaseThirdStage::BaseThirdStage()
{
	Points = 7;
}


GizahSecondStage::GizahSecondStage()
{
	CardCost.ModifyResource(Stone, 2);
	Points = 5;
}

RhodosSecondStage::RhodosSecondStage()
{
	CardCost.ModifyResource(Clay, 3);
}

void RhodosSecondStage::CardEffect(Player& player)
{
	player.MilitaryPoints += 2;
}