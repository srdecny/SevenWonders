#include "Engine.h"
#include "Cards.h"
#include "Wonders.hpp"
#include <ctime>

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

	std::srand(std::time(0)); // get random seed, or the shuffle will be the same every time
	std::random_shuffle(WondersToDistribute.begin(), WondersToDistribute.end());

	for (int l = 0; l < PlayerCount; l++)
	{
		Players[l].Wonder = GenerateWonder(WondersToDistribute[l]);
		Players[l].Wonder->InitialResource(Players[l]); // give the starting resource

		PlayersHands.push_back(std::vector<std::shared_ptr<BaseCard>>());
	}


	
}

void GameEngine::PresentCardsToPlayer(std::ostream &stream, Player &player, std::vector<std::shared_ptr<BaseCard>>& cards)
{
	std::vector<std::shared_ptr<BaseCard>> CanAfford;
	std::vector<std::shared_ptr<BaseCard>> CanNotAfford;
	std::map<std::shared_ptr<BaseCard>, std::vector<int>> CardPriceMap;
	bool CanAffordWonder = false;

	for (auto& card : cards)
	{
		auto cost = DetermineLowestBuyingCost(player, card); 

		if (card->CanPlayerAffordThisForFree(player)) CanAfford.push_back(card);
		else if (cost[0] <= player.Gold) CanAfford.push_back(card);
		else CanNotAfford.push_back(card);

		CardPriceMap.insert(std::make_pair(card, cost));

	}

	int PlayableIndex = 0;
	for (auto& Playable : CanAfford)
	{
		if (Playable->CanPlayerAffordThisForFree(player))
		{
			if (Playable->GoldCost == 0)
			{
				stream << "(Index " << std::to_string(PlayableIndex) << ") -- You can afford " << Playable->CardName() << " for free." << std::endl;
			}
			else
			{
				stream << "(Index " << std::to_string(PlayableIndex) << ") -- You can afford " << Playable->CardName();
				stream << " for a cost of: " << std::to_string(Playable->GoldCost);
				stream << std::endl;
			}
		}
		else
		{
			stream << "(Index " << std::to_string(PlayableIndex) << ") -- You can afford " << Playable->CardName();
			stream << " for a cost of: " << std::to_string(CardPriceMap[Playable][0]);
			stream << std::endl;
		}
		PlayableIndex++;
	}

	int UnplayableIndex = PlayableIndex;
	for (auto& Unplayable : CanNotAfford)
	{
		stream << "(Index " << std::to_string(UnplayableIndex) << ") -- You can not afford " << Unplayable->CardName() << "." << std::endl;
		UnplayableIndex++;
	}

	// get wonder if avaliable
	auto WonderBuilding = player.Wonder->CurrentBuilding;
	if (WonderBuilding == nullptr)
	{
		stream << "Your wonder is finished." << std::endl;
	}
	else
	{
		auto WonderCost = DetermineLowestBuyingCost(player, WonderBuilding);
		if (WonderBuilding->CanPlayerAffordThisForFree(player))
		{
			stream << "You can afford the next wonder stage for free." << std::endl;
			CanAffordWonder = true;
		}
		else if (WonderCost[0] <= player.Gold)
		{
			stream << "You can afford the next wonder stage for: " << std::to_string(WonderCost[0]) << "." << std::endl;
			CanAffordWonder = true;
		}
		else
		{
			stream << "You can't afford the next wonder stage." << std::endl;
		}
	
	}


	// REPL loop
	while (true)
	{
		stream << "Avaliable commands: play X; discard X; wonder X; peek left/right; exit. X is index of the card." << std::endl;
		std::string command;
		std::getline(std::cin, command);

		// because c++ doesn't support switch on strings, we have to use this horrible if-else tree

		if (command.substr(0, 4) == "play" && command.length() == 6) // because the index will alway be a single digit
		{
			int CardIndex = command[5] - '0'; // convert the index to int
			if (CardIndex >= 0 && CardIndex < PlayableIndex)
			{
				auto pair = std::make_pair(CanAfford[CardIndex], 0);
				//PlayedCardsQueue.push_back(pair);

				auto IndexToRemove = std::find(cards.begin(), cards.end(), CanAfford[CardIndex]);
				cards.erase(IndexToRemove);
				
				return;
			}
			else stream << "Invalid index!" << std::endl;
				
		}
		else if (command.substr(0, 6) == "discard" && command.length() == 9)
		{
			int CardIndex = command[5] - '0'; // convert the index to int
			if (CardIndex >= 0 && CardIndex < UnplayableIndex) // can discard unaffordable cards
			{
				DiscardedCard card;
				card.Play(player);

				auto IndexToRemove = std::find(cards.begin(), cards.end(), CanAfford[CardIndex]);
				cards.erase(IndexToRemove);
			}
		}
		else
		{
			stream << "Invalid command!" << std::endl;
		}


		

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



					int TotalCost = PaidToLeftThisPair + PaidToRightThisPair + card->GoldCost;

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
		return new Rhodos();
		break;
		//throw std::exception("Wonder not implemented!");
	}

}

void GameEngine::PrintPlayerStats(std::ostream& stream, Player& player)
{

	stream << "Avaliable Gold: " << std::to_string(player.Gold) << "; Military Points: " << std::to_string(player.MilitaryPoints) << std::endl;
	for (ResourceVector& vector : player.TradableResources)
	{
		stream << "Avaliable resources: " << vector.PrintResourceVector() << std::endl;
	}

	for (ScienceVector& vector : player.ScienceVectors)
	{
		stream << "Science symbols: " << vector.PrintScienceVector() << std::endl;
	}

}


void GameEngine::ProcessSingleTurn()
{
	// first, we deal with the live player, which is always the first one
	PresentCardsToPlayer(std::cout, Players[0], PlayersHands[0]);

	// then let the AI pick the cards
	for (int PlayerIndex = 1; PlayerIndex < (int)Players.capacity(); PlayerIndex++)
	{
		PresentCardstoAI(Players[PlayerIndex], PlayersHands[PlayerIndex]);
	}

	// then buy and play the cards at the same time
	for (auto& transaction : GoldTransactions)
	{
		DistributeGoldToNeighbours(transaction.first, *transaction.second);
	}

	for (auto& PlayedCard : PlayedCardsQueue)
	{
		PlayedCard.first->Play(*PlayedCard.second);
	}

}

void GameEngine::PresentCardstoAI(Player& player, std::vector<std::shared_ptr<BaseCard>>& cards)
{
	return;
}

void GameEngine::DistributeGoldToNeighbours(std::vector<int> GoldToDistribute, Player& player)
{
	player.LeftNeighbour->Gold += GoldToDistribute[1];
	player.RightNeighbour->Gold += GoldToDistribute[2];
}

void GameEngine::ProcessCardPurchase(std::shared_ptr<BaseCard> card, Player& player, std::vector<std::shared_ptr<BaseCard>>& hand)
{

	if (card->CanPlayerAffordThisForFree(player))
	{
		auto EmptyTransaction = std::vector<int>() = { 0,0,0 };
		GoldTransactions.push_back(std::make_pair(EmptyTransaction, &player));
	}
	else
	{
		GoldTransactions.push_back(std::make_pair(DetermineLowestBuyingCost(player, card), &player));
	}

	auto IndexToRemove = std::find(hand.begin(), hand.end(), card);
	hand.erase(IndexToRemove);

}