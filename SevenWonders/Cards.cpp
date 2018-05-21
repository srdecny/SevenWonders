#include "Cards.h"
#include "Player.h"
#include <iostream>
#include <sstream>


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

void BaseCard::Play(Player& player)
{
	CardEffect(player);
	player.Gold -= GoldCost;
    player.PlayedCards.push_back(shared_from_this());
}

void BaseCard::CardEffect(Player& player)
{

}

std::string BaseCard::GetCardInfoAndCost()
{
	std::stringstream info;
	info << CardInfo() << std::endl;
	info << "Card cost: " << CardCost.PrintResourceVector() << std::endl;
	if (GoldCost > 0) info << "This card also costs " << std::to_string(GoldCost) << " Gold." << std::endl;
	return info.str();
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

std::string SingleResourceBuilding::CardInfo()
{
	 return "This building produces a single resource: " + ResourcesName[ProducedResource];
}

void MultipleResourceBuilding::CardEffect(Player& player)
{
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

std::string MultipleResourceBuilding::CardInfo()
{
	std::stringstream info;
	info << "This building produces multiple resources. Only one resource is avaliable at given time." << std::endl;
	info << "Produced resources: ";
	for (auto resource : ProducedResources)
	{
		info << ResourcesName[resource] << " ";
	}
	return info.str();
}

void MilitaryBuilding::CardEffect(Player& player)
{
	player.MilitaryPoints += Power;
}

std::string MilitaryBuilding::CardInfo()
{
	return "This building provides " + std::to_string(Power) + " Military points.";
}

int GovernmentBuilding::ScorePoints(Player& player)
{
	return Points;
}

std::string GovernmentBuilding::CardInfo()
{
	return "This card gives you " + std::to_string(Points) + " Victory points.";
}

void ScienceBuilding::CardEffect(Player& player)
{
	player.ModifyScienceVectors(Symbol, 1);
}

std::string ScienceBuilding::CardInfo()
{
	return "This building gives you 1 " + SymbolsName[Symbol] + " Science symbol.";
}

int WonderBuilding::ScorePoints(Player& player)
{
	return Points;
}

void DiscardedCard::CardEffect(Player& player)
{
	player.Gold += 3;
}

int GuildBuilding::ScorePoints(Player& player)
{
	int CardCount = 0;
	for (auto card : player.LeftNeighbour->PlayedCards)
	{
		if (card->Type == ScoringType) CardCount++;
	}
	for (auto card : player.RightNeighbour->PlayedCards)
	{
		if (card->Type == ScoringType) CardCount++;
	}

	return CardCount * PointMultiplier;
}

std::string GuildBuilding::CardInfo()
{
	return "This card scores " + std::to_string(PointMultiplier) + " points for every " + CardTypesName[ScoringType] + " card your neighbours have.";
}