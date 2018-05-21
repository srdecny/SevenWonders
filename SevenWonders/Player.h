#pragma once
#include <vector>
#include <memory>
#include "GameUtilities.h"

class BaseCard;
class BaseWonder;

class Player
{
public:
	Player();
	~Player();

	std::vector<ResourceVector> TradableResources; // todo TradableResources
	std::vector<ScienceVector> ScienceVectors;
    
    // shared_ptr because one card can appear multiple times in games with higher player count
    // and we want to have only one instance of each card class for lower memory usage
    std::vector<std::shared_ptr<BaseCard>> PlayedCards;
	void ModifyTradableResources(Resources resource, int change);
	void ModifyScienceVectors(ScienceSymbols symbol, int change);

	int Gold;
	int CommonResourceCostLeft = 2;
	int CommonResourceCostRight = 2;
	int RareResourceCost = 2;

	int MilitaryLoses = 0;
	int MilitaryWins = 0;

	int MilitaryPoints = 0;

	BaseWonder* Wonder;

	Player* LeftNeighbour;
	Player* RightNeighbour;

};

