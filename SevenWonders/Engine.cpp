#include "Engine.h"
#include "Cards.h"
#include "Wonders.hpp"

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

	
	// randomly assign wonders to players
	std::vector<int> WondersToDistribute = { 0, 1, 2, 3, 4, 5, 6, 7 };
	std::random_shuffle(WondersToDistribute.begin(), WondersToDistribute.end());
	for (int k = 7 - PlayerCount; k > 0; k--) WondersToDistribute.pop_back(); // discard excess wonders

	for (int l = 0; l < PlayerCount; l++)
	{
		Players[l].Wonder = GenerateWonder(WondersToDistribute[l]);
	}
	
}

void GameEngine::PresentCardsToPlayer(std::ostream &stream, Player &player, std::vector<std::shared_ptr<BaseCard>> cards)
{
	stream << "Cards you can play this turn: " << std::endl;
	for (auto& card : cards)
	{
        auto cost = DetermineLowestBuyingCost(player, card); // if 0 then can't buy it from neighbours
        
        if (card->CanPlayerAffordThis(player)) stream << "You can afford this for free: " << card->CardName << std::endl;
        else if (cost[0] != 0 || cost[0] > player.Gold) stream << "You can afford this for a minimum cost of: " << cost[0] << ", " << card->CardName << std::endl;
        else  stream << "You can't afford this card: " << card->CardName << std::endl;
	}
}

bool GameEngine::PlayerCanAffordCard(Player &player, std::shared_ptr<BaseCard> card)
{
	throw std::invalid_argument("NOT IMPLEMENTED");
}

std::vector<int> GameEngine::DetermineLowestBuyingCost(Player &player, std::shared_ptr<BaseCard> card)
{
	// most of the time players will have only one or two resource vectors, so performance should be OK
	// the rough cap of different resource vectors in base game is 16 (caravanserai + appropriate wonder)

	int MinimumCost = 1000; // the real cost won't ever be bigger, so it's safe
	int GoldPaidToLeft = 0;
	int GoldPaidToRight = 0;

	for (ResourceVector &PlayerResource : player.TradableResources)
	{
		ResourceVector ResourcesToBuy = card->CardCost - PlayerResource;

		// we need to loop over all possible combinations of neighbour's resources
		for (ResourceVector &LeftNeighbourResource : player.LeftNeighbour->TradableResources)
		{
			for (ResourceVector &RightNeighbourResource : player.RightNeighbour->TradableResources)
			{
				int CostOfThisPair = 0; // how much will this pair cost us
				int PaidToLeftThisPair = 0;
				int PaidToRightThisPair = 0;

				for (int i = 0; i <= 6; i++) // check individual resources
				{
					int AmountToBuy = ResourcesToBuy[i];

					if (LeftNeighbourResource[i] + RightNeighbourResource[i] < AmountToBuy)
					{
						break; // this pair of neighbour resources doesn't have enough resources we need, so just discard it
					}

					if (i <= 3) // common resources, we might have some discounts for either side
					{
						if (player.CommonResourceCostLeft == 1) // discount for left
						{
							int CanBuyFromLeft = std::min(AmountToBuy, LeftNeighbourResource[i]);
							PaidToLeftThisPair += player.CommonResourceCostLeft * CanBuyFromLeft;
							PaidToRightThisPair += player.CommonResourceCostRight * (AmountToBuy - CanBuyFromLeft);
						}
						else // discount for right
						{
							int CanBuyFromRight = std::min(AmountToBuy, RightNeighbourResource[i]);
							PaidToRightThisPair += player.CommonResourceCostRight * CanBuyFromRight;
							PaidToLeftThisPair += player.CommonResourceCostLeft * (AmountToBuy - CanBuyFromRight);
						}
					}
					else // rare resources, discount is always for both neighbours
					{
						int CanBuyFromLeft = std::min(AmountToBuy, LeftNeighbourResource[i]);
						PaidToLeftThisPair += player.RareResourceCost * CanBuyFromLeft;
						PaidToRightThisPair += player.RareResourceCost * (AmountToBuy - CanBuyFromLeft);
					}



					int TotalCost = PaidToLeftThisPair + PaidToRightThisPair;

					if (MinimumCost > TotalCost && TotalCost > 0)
					{
						MinimumCost = TotalCost;
						GoldPaidToLeft = PaidToLeftThisPair;
						GoldPaidToRight = PaidToRightThisPair;
					}
				}

			}
		}
	
	}
	return std::vector<int>{ MinimumCost, GoldPaidToLeft, GoldPaidToRight};
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

int GameEngine::ScoreSciencePoints(Player &player)
{
	int ScoredPoints = 0;

	for (ScienceVector &vector : player.ScienceVectors)
	{
		int VectorScore = 0;
		VectorScore += *std::min_element(vector.ScienceArray.begin(), vector.ScienceArray.end()) * 7;
		for (int i = 0; i <= 2; i++)
		{
			VectorScore += vector.ScienceArray[i] * vector.ScienceArray[i];
		}

		if (VectorScore > ScoredPoints) ScoredPoints = VectorScore;
	}

	return ScoredPoints;
}

BaseWonder* GameEngine::GenerateWonder(int WonderIndex)
{
	switch (WonderIndex)
	{
	case 1:
		return new Gizah();
		break;

	case 2:
		return new Rhodos();
		break;

	default:
		return new Gizah();
		break;
		//throw std::exception("Wonder not implemented!");
	}

}
