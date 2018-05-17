#include "Cards.h"
#include "Player.h"
#include <iostream>


BaseCard::BaseCard()
{

}

BaseCard::~BaseCard()
{
	
}

bool BaseCard::CanPlayerAffordThis(Player& player)
{
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

bool CardThatCostGold::CanPlayerAffordThis(Player& player)
{
	bool CanAfford = player.Gold >= 1;
	return CanAfford && BaseCard::CanPlayerAffordThis(player); // gotta have gold AND resources
}

void BaseCard::Play(Player& player)
{
	CardEffect(player);
    player.PlayedCards.push_back(shared_from_this());
}

void BaseCard::CardEffect(Player& player)
{

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

	for (ResourceVector vector : player.TradableResources)
	{
		for (Resources resource : ProducedResources)
		{
			vector.ModifyResource(resource, 1);
			NewResources.push_back(vector);
		}
	}

	player.TradableResources.clear();

	for (ResourceVector vector : NewResources)
	{
		player.TradableResources.push_back(vector);
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