#pragma once
#include <vector>
#include "Cards.h"
#include <memory>
class BaseCard;

class Player
{
public:
	Player();
	~Player();

	std::vector<ResourceVector> AvaliableResources; // todo TradableResources
    
    // shared_ptr because one card can appear multiple times in the game with higher player count
    // and we want to have only one instance of each card class for lower memory usage
    std::vector<std::shared_ptr<BaseCard>> PlayedCards;
	void ModifyAvaliableResource(Resources resource, int change);

	int Gold;
	int CommonResourceCostLeft = 2;
	int CommonResourceCostRight = 2;
	int RareResourceCost = 2;
    
	Player* LeftNeighbour;
	Player* RightNeighbour;

	int MilitaryPoints = 0;
};

