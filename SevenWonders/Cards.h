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
	BaseCard();
	~BaseCard();

	ResourceVector CardCost;

	std::string GetCardInfoAndCost();
	virtual std::string CardInfo() { return "Card info not implemented!"; };

	std::string CardName();
	std::vector<int> PlayerCount;
	CardTypes Type;
	int ID;
	int GoldCost = 0;
	std::vector<int> PrerequisiteCards;


	bool CanPlayerAffordThisForFree(Player& player);
};

class SingleResourceBuilding : public BaseCard
{
public:
	Resources ProducedResource;
	int Amount;
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class MilitaryBuilding : public BaseCard
{
public:
	int Power;
	void CardEffect(Player& player) override;
	MilitaryBuilding() { Type = Military; };
	std::string CardInfo() override;

};

class GovernmentBuilding : public BaseCard
{
public:
	int Points;
	int ScorePoints(Player& player) override;
	GovernmentBuilding() { Type = Government; };
	std::string CardInfo() override;

};

class MultipleResourceBuilding : public BaseCard
{
public:
	void CardEffect(Player& player) override; // will also make player pay gold
	std::vector<Resources> ProducedResources;
	MultipleResourceBuilding() { Type = CommonResource; };
	std::string CardInfo() override;

};

class ScienceBuilding : public BaseCard
{
public:
	CardTypes Type = Science;
	ScienceSymbols Symbol;
	void CardEffect(Player& player) override;
	ScienceBuilding() { Type = Science; };
	std::string CardInfo() override;

};

class MerchantBuilding : public BaseCard
{
public:
	CardTypes Type = Merchant;
	virtual void CardEffect(Player& player) override { return; };
	MerchantBuilding() { Type = Merchant; };

};

class WonderBuilding : public BaseCard
{
public:
	virtual void CardEffect(Player& player) override { return; };
	int ScorePoints(Player& player) override;
	std::string CardInfo() override { return "Not implemented!"; };
	int Points;
	CardTypes Type = Wonder;
	WonderBuilding() { Type = Wonder; };
};

 class DiscardedCard : public BaseCard
{
public:
	void CardEffect(Player& player) override;
};