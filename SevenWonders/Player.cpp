#include "stdafx.h"
#include "Player.h"
#include "Wonders.hpp"
#include <array>


Player::Player()
{
	TradableResources.push_back(ResourceVector());
	ScienceVectors.push_back(ScienceVector());
	Gold = 3;
}


Player::~Player()
{
	
}

void Player::ModifyTradableResources(Resources resource, int change)
{
	for (ResourceVector &v : TradableResources)
	{
		v.ResourcesArray[resource] += change;
	}
}

void Player::ModifyScienceVectors(ScienceSymbols symbol, int change)
{
	for (ScienceVector &v : ScienceVectors)
	{
		v.ScienceArray[symbol] += change;
	}
}
