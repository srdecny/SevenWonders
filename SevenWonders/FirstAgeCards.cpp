
#include "FirstAgeCards.h"
#include <vector>
#include <iostream>



void WoodenWall::CardEffect(Player & player)
{
	player.MilitaryPoints += 1;
}

WoodenWall::WoodenWall()
{
	CardName = "Wooden Wall";
	CardCost.ModifyResource(Wood, 1);
	PlayerCount = { 3, 7 };
	type = Military;
	
}


void LumberMill::CardEffect(Player& player)
{
	player.ModifyAvaliableResource(Wood, 1);
}

LumberMill::LumberMill()
{
	CardName = "Lumber Mill";
	PlayerCount = { 3, 4 };
	type = CommonResource;
}

ClayMine::ClayMine()
{
	CardName = "Clay Mine";
	PlayerCount = { 3 };
	GoldCost = 1;
	type = CommonResource;
}

void ClayMine::CardEffect(Player & player)
{
	player.Gold -= 1;
	// make all new permutations avaliable with the dual resources
    // can use only one of the two resources at one time
	std::vector<ResourceVector> originalResources = player.AvaliableResources;
	for (ResourceVector &vector : originalResources) { vector.ModifyResource(Clay, 1); }
	for (ResourceVector &vector : player.AvaliableResources) { vector.ModifyResource(Iron, 1); }
	for (ResourceVector &vector : originalResources) { player.AvaliableResources.push_back(vector); }
}


int Statue::ScorePoints(Player &player) { return 2; }
Statue::Statue()
{
    CardName = "Statue";
    CardCost.ModifyResource(Stone, 1);
    type = Government;
    
}

