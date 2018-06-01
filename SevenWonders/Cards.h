#pragma once
#include "GameUtilities.h"
#include <string>
#include <vector>
#include <memory>

class Player;


class BaseCard : public std::enable_shared_from_this<BaseCard>
{
public:
	virtual void Play(Player&);
    virtual void CardEffect(Player&);
    virtual int ScorePoints(Player&) {return 0;}
	
	ResourceVector CardCost;
	int GoldCost = 0;

	std::string GetCardInfoAndCost(); // calls CardInfo in itself and prints the card name
	virtual std::string CardInfo() { return "Card info not implemented!"; };

	std::string CardName();
	std::vector<int> PlayerCount; // how many copies are in play for a given player count
	CardTypes Type;
	int ID; // used when checking prerequisties. using int to save memory.
	std::vector<int> PrerequisiteCards;

	bool CanPlayerAffordThisForFree(Player& player); // checks if the player has enough resources or has a prerequisite card. checks goldcost, too.
};

class SingleResourceBuilding : public BaseCard
{ 
public:
	// MUST assign the Type in children class constructor (Common/Rare resource)
	Resources ProducedResource;
	int Amount;
	// gives a player Amount of ProducedResource
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class MilitaryBuilding : public BaseCard
{
public:
	int Power;
	// gives player Power to his MilitaryPower
	void CardEffect(Player& player) override;
	MilitaryBuilding() { Type = Military; };
	std::string CardInfo() override;

};

class GovernmentBuilding : public BaseCard
{
public:
	int Points = 0;
	// will return Points
	int ScorePoints(Player& player) override;
	GovernmentBuilding() { Type = Government; };
	std::string CardInfo() override;

};

class MultipleResourceBuilding : public BaseCard
{
public:
	// Gives the player a SINGLE resource of ProducedResources at a given time, basically a wildcard/joker.
	void CardEffect(Player& player) override;
	std::vector<Resources> ProducedResources;
	MultipleResourceBuilding() { Type = CommonResource; };
	std::string CardInfo() override;

};

class ScienceBuilding : public BaseCard
{
public:
	ScienceSymbols Symbol;
	// gives the player the Symbol
	void CardEffect(Player& player) override;
	ScienceBuilding() { Type = Science; };
	std::string CardInfo() override;

};

class MerchantBuilding : public BaseCard
{
public:
	// every MerchantBuilding has unique effect, usually gives some gold
	virtual void CardEffect(Player& player) override { return; };
	MerchantBuilding() { Type = Merchant; };

};

class WonderBuilding : public BaseCard
{
public:
	// Similar to MerchantBuilding, can do anything
	virtual void CardEffect(Player& player) override { return; };
	int ScorePoints(Player& player) override;
	std::string CardInfo() override { return "Not implemented!"; };
	int Points = 0;
	WonderBuilding() { Type = Wonder; };
};

class GuildBuilding : public BaseCard
{
public:
	// Usually GuildBuilding gives PointMultiplier times the amount of a ScoringType buildings player's neighbours have
	virtual int ScorePoints(Player& player) override;
	virtual std::string CardInfo() override;
	GuildBuilding() { Type = Guild; PlayerCount = { 3 }; }; // every guild can appear only once
	CardTypes ScoringType;
	int PointMultiplier;
};

 class DiscardedCard : public BaseCard
{
public:
	// just gives the player 3 gold
	void CardEffect(Player& player) override;
};