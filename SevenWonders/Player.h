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

	std::vector<ResourceVector> AvaliableResources;
	std::vector<ScienceVector> ScienceVectors;

	void ModifyTradableResources(Resources resource, int change);
	void ModifyScienceVectors(ScienceSymbols symbol, int change);

    
    // shared_ptr because one card can appear multiple times in games with higher player count
    // and we want to have only one instance of each card class for lower memory usage
    std::vector<std::shared_ptr<BaseCard>> PlayedCards;

	int Gold = 3;
	int CommonResourceCostLeft = 2;
	int CommonResourceCostRight = 2;
	int RareResourceCost = 2;

	int MilitaryLoses = 0;
	int MilitaryWins = 0;

	int MilitaryPoints = 0;

	// this could be unique_ptr, but I failed at making it work
	// there was trouble when pushing new Player instance into a vector
	std::shared_ptr<BaseWonder> Wonder;

	// using raw pointers, because the Players are owned by the engine
	// weak_ptr has to be constructed from shared or another weak pointer, so it's unusable, unfortunately
	Player* LeftNeighbour;
	Player* RightNeighbour;
	int PlayerIndex;

};

