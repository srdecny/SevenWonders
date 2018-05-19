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

	std::string CardName();
	std::vector<int> PlayerCount;
	CardTypes Type;
	int ID;
	int GoldCost = 0;
	std::vector<int> PrerequisiteCards;


	bool CanPlayerAffordThisForFree(Player& player);
};

class CardThatCostGold : public BaseCard
{
public:
	int GoldCost;
	bool CanPlayerAffordThisForFree(Player& player);
	void Play(Player&) override;
};

class SingleResourceBuilding : public BaseCard
{
public:
	Resources ProducedResource;
	int Amount;
	void CardEffect(Player& player) override;
};

class MilitaryBuilding : public BaseCard
{
	CardTypes Type = Military;
public:
	int Power;
	void CardEffect(Player& player) override;
};

class GovernmentBuilding : public BaseCard
{
	CardTypes Type = Government;
public:
	int Points;
	int ScorePoints(Player& player) override;
};

class MultipleResourceBuilding : public CardThatCostGold
{
public:
	void CardEffect(Player& player) override; // will also make player pay gold
	std::vector<Resources> ProducedResources;
	int GoldCost;
	CardTypes Type = CommonResource;
};

class ScienceBuilding : public BaseCard
{
public:
	CardTypes Type = Science;
	ScienceSymbols Symbol;
	void CardEffect(Player& player) override;
};

class MerchantBuilding : public BaseCard
{
public:
	CardTypes Type = Merchant;
	virtual void CardEffect(Player& player) override { return; };
};

class WonderBuilding : public BaseCard
{
public:
	virtual void CardEffect(Player& player) override { return; };
	int ScorePoints(Player& player) override;
	int Points;
	CardTypes Type = Wonder;



};