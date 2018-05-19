#include "Cards.h"
#include "Player.h"
#include <iostream>


BaseCard::BaseCard()
{

}

BaseCard::~BaseCard()
{
	
}

bool BaseCard::CanPlayerAffordThisForFree(Player& player)
{
	if (player.Gold < GoldCost) return false;

	for (ResourceVector &vector : player.TradableResources)
	{
		if (vector >= CardCost) return true;
	}

	for (auto &PlayedCard : player.PlayedCards)
	{
		for (auto prerequisite : PrerequisiteCards)
		{
			if (PlayedCard->ID == prerequisite) return true;
		}
	}

	return false;
}

/*
bool CardThatCostGold::CanPlayerAffordThisForFree(Player& player)
{
	
	if (player.Gold < GoldCost) return false;
	return BaseCard::CanPlayerAffordThisForFree(player); // gotta have gold AND resources
	
}

void CardThatCostGold::Play(Player& player)
{
	player.Gold -= GoldCost;
	CardEffect(player);
}
*/

void BaseCard::Play(Player& player)
{
	CardEffect(player);
    player.PlayedCards.push_back(shared_from_this());
}

void BaseCard::CardEffect(Player& player)
{

}

std::string BaseCard::CardName()
{
	std::string result = typeid(*this).name(); // this is almost certainly wrong in some way
	return result.substr(6, result.length() - 6); // discard the "class "
}

void SingleResourceBuilding::CardEffect(Player& player)
{
	player.ModifyTradableResources(ProducedResource, Amount);
}

void MultipleResourceBuilding::CardEffect(Player& player)
{
	player.Gold -= GoldCost;

	// for every avaliable ResourceVector, make new vectors based on the avaliable resources
	// so only one resource from AvaliableResource is avaliable at a given time
	std::vector<ResourceVector> NewResources;

	for (ResourceVector OldVector : player.TradableResources)
	{
		for (Resources Resource : ProducedResources)
		{
			auto NewVector = ResourceVector(OldVector);
			NewVector.ModifyResource(Resource, 1);
			NewResources.push_back(NewVector);
		}
	}

	player.TradableResources.clear();

	for (ResourceVector NewVector : NewResources)
	{
		player.TradableResources.push_back(NewVector);
	}
}

void MilitaryBuilding::CardEffect(Player& player)
{
	player.MilitaryPoints += Power;
}

int GovernmentBuilding::ScorePoints(Player& player)
{
	return Points;
}

void ScienceBuilding::CardEffect(Player& player)
{
	player.ModifyScienceVectors(Symbol, 1);
}

int WonderBuilding::ScorePoints(Player& player)
{
	return Points;
}

void DiscardedCard::CardEffect(Player& player)
{
	player.Gold += 3;
}