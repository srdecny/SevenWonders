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

SingleResourceProducer::SingleResourceProducer(Resources resource, int count)
{
	ProducedResource = resource;
	Amount = count;
}

void SingleResourceProducer::CardEffect(Player& player)
{
	player.ModifyTradableResources(ProducedResource, Amount);
}
