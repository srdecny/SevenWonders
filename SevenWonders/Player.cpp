#include "stdafx.h"
#include "Player.h"
#include "Wonders.hpp"
#include <array>


Player::Player()
{
	AvaliableResources.push_back(ResourceVector());
	ScienceVectors.push_back(ScienceVector());
	Gold = 3;
}


void Player::ModifyTradableResources(Resources resource, int change)
{
	for (ResourceVector &v : AvaliableResources)
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
