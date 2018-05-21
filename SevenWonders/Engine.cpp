#include "Engine.h"
#include "Cards.h"
#include "Wonders.hpp"
#include "CardGenerator.hpp"
#include <ctime>
#include <algorithm>

GameEngine::GameEngine(int count)
{
	PlayerCount = count;
}

GameEngine::~GameEngine()
{
}

void GameEngine::InitializeTheGame()
{
	if (PlayerCount <= 2 || PlayerCount > 7) throw std::invalid_argument("Invalid player count!");

	for (int i = 0; i < PlayerCount; i++)
	{
		Players.push_back(Player());
		Players[i].Gold = 3; 
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
	std::map<std::shared_ptr<BaseCard>, std::vector<int>> CardPriceMap;
	std::vector<int> PlayableCardIndexes;
	std::vector<int> UnplayableCardIndexes;
	bool CanAffordWonder = false;

	int index = 0;
	for (auto& card : cards)
	{
		auto cost = DetermineLowestBuyingCost(player, card); 

		if (card->CanPlayerAffordThisForFree(player)) PlayableCardIndexes.push_back(index);
		else if (cost[0] <= player.Gold) PlayableCardIndexes.push_back(index);
		else UnplayableCardIndexes.push_back(index);

		CardPriceMap.insert(std::make_pair(card, cost));
		index++;

	}

	for (int PlayableIndex : PlayableCardIndexes)
	{
		auto Playable = cards[PlayableIndex];
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
	}

	for (int UnplayableIndex : UnplayableCardIndexes)
	{
		auto Unplayable = cards[UnplayableIndex];
		stream << "(Index " << std::to_string(UnplayableIndex) << ") -- You can not afford " << Unplayable->CardName() << "." << std::endl;
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
		stream << "Avaliable commands: play X; discard X; wonder X; info X/wonder; stats left/right/me; exit. X is index of the card." << std::endl;
		std::string command;
		std::getline(std::cin, command);
		stream << std::endl;

		// because c++ doesn't support switch on strings, we have to use this horrible if-else tree

		if (command.substr(0, 4) == "play" && command.length() == 6) // because the index will alway be a single digit
		{
			int CardIndex = command[5] - '0'; // convert the index to int
			if (std::find(PlayableCardIndexes.begin(), PlayableCardIndexes.end(), CardIndex) != PlayableCardIndexes.end())
			{
				ProcessCardPurchase(cards[CardIndex], cards[CardIndex], player, cards);
				return;
			}
			else stream << "Invalid index!" << std::endl;
				
		}
		else if (command.substr(0, 7) == "discard" && command.length() == 9)
		{
			int CardIndex = command[8] - '0'; // convert the index to int
			if (CardIndex >= 0 && CardIndex < (int)cards.size()) // can discard unaffordable cards
			{
				auto discard = std::make_shared<DiscardedCard>();
				ProcessCardPurchase(discard, cards[CardIndex], player, cards);
				break;
			}
			else stream << "Invalid index!" << std::endl;
		}
		else if (command.substr(0, 6) == "wonder" && command.length() == 8)
		{
			if (!CanAffordWonder) stream << "Can't afford wonder!" << std::endl;
			else
			{
				int CardIndex = command[7] - '0'; // convert the index to int
				if (CardIndex >= 0 && CardIndex < (int)cards.size()) // can discard unaffordable cards
				{
					ProcessCardPurchase(player.Wonder->CurrentBuilding, cards[CardIndex], player, cards);
					player.Wonder->GetNextWonderBuilding();
					break;
				}
			}
		}
		else if(command.substr(0, 5) == "stats" && command.length() <= 12)
		{
			if (command.substr(6, 4) == "left")
			{
				stream << "Left neighbour stats: " << std::endl; PrintPlayerStats(std::cout, *player.LeftNeighbour);
			}
			else if (command.substr(6, 5) == "right")
			{
				stream << "Right neighbour stats: " << std::endl; PrintPlayerStats(std::cout, *player.RightNeighbour);
			}
			else if (command.substr(6, 2) == "me")
			{
				stream << "Your stats: " << std::endl; PrintPlayerStats(std::cout, player);
			}
			else stream << "Invalid command!" << std::endl;

		}
		else if (command.substr(0, 4) == "info" && command.length() <= 11) 
		{
			if (command.length() == 6)
			{
				int CardIndex = command[5] - '0'; // convert the index to int
				if (CardIndex >= 0 && CardIndex < (int)cards.size())
				{
					stream << cards[CardIndex]->GetCardInfoAndCost();
				}
				else stream << "Invalid index!" << std::endl;
			}
			else if (command.length() == 11)
			{
				if (command.substr(5, 6) == "wonder")
				{
					if (player.Wonder->CurrentBuilding == nullptr)
					{
						stream << "Your wonder is finished." << std::endl;
					}
					else
					{
						stream << player.Wonder->CurrentBuilding->GetCardInfoAndCost();
					}
				}
				else stream << "Invalid command!" << std::endl;
			}
			else stream << "Invalid command!" << std::endl;
		}
		else if (command.substr(0, 4) == "exit")
		{
			exit(0);
		}
		else
		{
			stream << "Invalid command!" << std::endl;
		}
	}

	stream << std::endl;	
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
	ScoredPoints += player.MilitaryLoses;
	ScoredPoints += player.MilitaryWins;
	ScoredPoints += ScoreSciencePoints(player);
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

	stream << "Avaliable Gold: " << std::to_string(player.Gold) << "; Military Points: " << std::to_string(player.MilitaryPoints) << "; Wonder: " << player.Wonder->WonderName << std::endl;
	for (ResourceVector& vector : player.TradableResources)
	{
		stream << "Avaliable resources: " << vector.PrintResourceVector() << std::endl;
	}

	for (ScienceVector& vector : player.ScienceVectors)
	{
		stream << "Science symbols: " << vector.PrintScienceVector() << std::endl;
	}

	stream << "Scored points: " << std::to_string(ScorePlayerPoints(player)) << std::endl;
	stream << std::endl;

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

	std::rotate(PlayersHands.begin(), PlayersHands.begin() + 1, PlayersHands.end()); // pass the cards clockwise

	GoldTransactions.clear();
	PlayedCardsQueue.clear();

	PrintPlayerStats(std::cout, Players[0]);


}

void GameEngine::PresentCardstoAI(Player& player, std::vector<std::shared_ptr<BaseCard>>& cards)
{
	ProcessCardPurchase(cards[0], cards[0], player, cards); // always plays the first card
}

void GameEngine::DistributeGoldToNeighbours(std::vector<int> GoldToDistribute, Player& player)
{
	player.LeftNeighbour->Gold += GoldToDistribute[1];
	player.RightNeighbour->Gold += GoldToDistribute[2];
}

void GameEngine::ProcessCardPurchase(std::shared_ptr<BaseCard> CardToPlay, std::shared_ptr<BaseCard>CardToDiscard, Player& player, std::vector<std::shared_ptr<BaseCard>>& hand)
{

	if (CardToPlay->CanPlayerAffordThisForFree(player))
	{
		auto EmptyTransaction = std::vector<int>() = { 0,0,0 };
		GoldTransactions.push_back(std::make_pair(EmptyTransaction, &player));
	}
	else
	{
		GoldTransactions.push_back(std::make_pair(DetermineLowestBuyingCost(player, CardToPlay), &player));
	}

	PlayedCardsQueue.push_back(std::make_pair(CardToPlay, &player));

	auto IndexToRemove = std::find(hand.begin(), hand.end(), CardToDiscard);
	hand.erase(IndexToRemove);

}

void GameEngine::PlayTheGame()
{
	InitializeTheGame();

	Generator CardGenerator;
	PlayersHands = CardGenerator.GenerateFirstAgeCards(PlayerCount);
	
	for (int turn = 0; turn < 6; turn++)
	{
		ProcessSingleTurn();
	}
	CalculateMilitaryFights(1);
	PrintPlayerStats(std::cout, Players[0]);
}

void GameEngine::CalculateMilitaryFights(int PointsForWin)
{

	// since everyone will compare himself and his left neighbour, it will circle around
	// so player's both neighbours will be compared in the end
	for (Player& player : Players)
	{
		if (player.MilitaryPoints > player.LeftNeighbour->MilitaryPoints)
		{
			player.MilitaryWins += PointsForWin;
			player.LeftNeighbour->MilitaryLoses -= 1;
		}
		else if (player.MilitaryPoints < player.LeftNeighbour->MilitaryPoints)
		{
			player.LeftNeighbour->MilitaryWins += PointsForWin;
			player.MilitaryLoses -= 1;
		}
	}
}

