#include "Player.h"
#include "Wonders.hpp"
#include <array>


Player::Player()
{
	Wonder = new Gizah();
	TradableResources.push_back(ResourceVector());
	Gold = 3;
}


Player::~Player()
{
	Wonder->~BaseWonder();
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
