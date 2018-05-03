#include "Player.h"
#include <array>


Player::Player()
{
	AvaliableResources.push_back(ResourceVector());
	Gold = 3;
}


Player::~Player()
{
}

void Player::ModifyAvaliableResource(Resources resource, int change)
{
	for (ResourceVector &v : AvaliableResources)
	{
		v.ResourcesArray[resource] += change;
	}
}
