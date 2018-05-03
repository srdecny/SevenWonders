#pragma once
#include "GameUtilities.h"
#include "Player.h"
#include <string>
#include <vector>
#include <memory>

class Player;

class BaseCard : public std::enable_shared_from_this<BaseCard>
{
public:
	void Play(Player&);
    virtual void CardEffect(Player&);
    virtual int ScorePoints(Player&) {return 0;}
	BaseCard();
	~BaseCard();

	ResourceVector CardCost;

	std::string CardName;
	std::vector<int> PlayerCount;
	CardTypes type;

	bool CanPlayerAffordThis(Player& player);
};

class CardThatCostGold : public BaseCard
{
public:
	int GoldCost;
	bool CanPlayerAffordThis(Player& player); // checks if player has enough gold too
};

class CardsThatScorePoints : public BaseCard
{
    int ScorePoints(Player& player);
};

