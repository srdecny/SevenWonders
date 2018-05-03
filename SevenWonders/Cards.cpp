#include "Cards.h"
#include <iostream>


BaseCard::BaseCard()
{

}

BaseCard::~BaseCard()
{
	
}

bool BaseCard::CanPlayerAffordThis(Player& player)
{
	bool CanAfford = false;
	for (ResourceVector &vector : player.AvaliableResources)
	{
		if (vector >= CardCost) CanAfford = true;
	}

	return CanAfford;
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

int CardsThatScorePoints::ScorePoints(Player &player)
{
    throw std::exception();
};

