#include "Engine.h"


GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::InitializeTheGame(int PlayerCount)
{
	if (PlayerCount <= 2 || PlayerCount > 7) throw std::invalid_argument("Invalid player count!");

	for (int i = 0; i < PlayerCount; i++)
	{
		Players.push_back(Player());
		Players[i].Gold = i; // TEST PURPOSES
	}

    // assign neighbours
	for (int j = 0; j < PlayerCount; j++)
	{
		// because c++ doesnt have proper modulo we have to use this weird formula instead
		Players[j].LeftNeighbour = &Players[((j - 1) % PlayerCount + PlayerCount) % PlayerCount];
		Players[j].RightNeighbour = &Players[((j + 1) % PlayerCount + PlayerCount) % PlayerCount];

	}
    
}

void GameEngine::PresentCardsToPlayer(std::ostream &stream, Player &player, std::vector<std::shared_ptr<BaseCard>> cards)
{
	stream << "Cards you can play this turn: " << std::endl;
	for (auto& card : cards)
	{
        int cost = DetermineLowestBuyingCost(player, card); // if 0 then can't buy it from neighbours
        
        if (card->CanPlayerAffordThis(player)) stream << "You can afford this for free: " << card->CardName << std::endl;
        else if (cost != 0 || cost > player.Gold) stream << "You can afford this for a minimum cost of: " << DetermineLowestBuyingCost(player, card) << ", " << card->CardName << std::endl;
        else  stream << "You can't afford this card: " << card->CardName << std::endl;
	}
}

bool GameEngine::PlayerCanAffordCard(Player &player, std::shared_ptr<BaseCard> card)
{
	throw std::invalid_argument("NOT IMPLEMENTED");
}

int GameEngine::DetermineLowestBuyingCost(Player &player, std::shared_ptr<BaseCard> card)
{
	// most of the time players will have only one or two resource vectors, so performance should be OK
	// the rough cap of different resource vectors in base game is 16 (caravanserai + appropriate wonder)

	int MinimumCost = 1000; // the real cost won't ever be bigger, so it's safe

	for (ResourceVector &PlayerResource : player.AvaliableResources)
	{
		ResourceVector ResourcesToBuy = card->CardCost - PlayerResource;

		// we need to loop over all possible combinations of neighbour's resources
		for (ResourceVector &LeftNeighbourResource : player.LeftNeighbour->AvaliableResources)
		{
			for (ResourceVector &RightNeighbourResource : player.RightNeighbour->AvaliableResources)
			{
				int CostOfThisPair = 0; // how much will this pair cost us

				for (int i = 0; i <= 6; i++) // check individual resources
				{
					if (LeftNeighbourResource.ResourcesArray[0] + RightNeighbourResource.ResourcesArray[0] < ResourcesToBuy.ResourcesArray[0])
					{
						break; // this pair of neighbour resources doesn't have enough resources we need, so just discard it
					}

					if (i <= 4) // common resources, we might have some discounts for either side
					{
						// we don't have any discounts or we have both of them
						if (player.CommonResourceCostLeft == player.CommonResourceCostRight)
						{
							CostOfThisPair += player.CommonResourceCostLeft*ResourcesToBuy.ResourcesArray[i];
						}
						else // we have discount when buying from one neighbour
						{
							if (player.CommonResourceCostLeft == 1) // discount for left neighbour
							{
								int HowMuchWeCanBuyFromLeft;
								if (ResourcesToBuy.ResourcesArray[i] <= LeftNeighbourResource.ResourcesArray[i]) // can buy everything from left
								{
									HowMuchWeCanBuyFromLeft = ResourcesToBuy.ResourcesArray[i];
								}
								else // can buy just something
								{
									HowMuchWeCanBuyFromLeft = LeftNeighbourResource.ResourcesArray[i];
								}

								CostOfThisPair += HowMuchWeCanBuyFromLeft + 2 * (ResourcesToBuy.ResourcesArray[i] - HowMuchWeCanBuyFromLeft);
							}
							else // discount for right neighbour
							{
								int HowMuchWeCanBuyFromRight;
								if (ResourcesToBuy.ResourcesArray[i] <= RightNeighbourResource.ResourcesArray[i]) // can buy everything from left
								{
									HowMuchWeCanBuyFromRight = ResourcesToBuy.ResourcesArray[i];
								}
								else
								{
									HowMuchWeCanBuyFromRight = RightNeighbourResource.ResourcesArray[i];
								}

								CostOfThisPair += HowMuchWeCanBuyFromRight + 2 * (ResourcesToBuy.ResourcesArray[i] - HowMuchWeCanBuyFromRight);

							}
						}
					}
					else // rare resources, discount is always for both neighbours
					{
						CostOfThisPair += player.RareResourceCost*ResourcesToBuy.ResourcesArray[i];
					}

				}

				if (CostOfThisPair < MinimumCost ) MinimumCost = CostOfThisPair;

			}
		}
	
	}
	return MinimumCost;
}

int GameEngine::ScorePlayerPoints(Player &player)
{
    int ScoredPoints = 0;
    for (std::shared_ptr<BaseCard>& card : player.PlayedCards)
    {
        ScoredPoints += card->ScorePoints(player);
    }
    return ScoredPoints;
}
