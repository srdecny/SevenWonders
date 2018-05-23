#include "stdafx.h"
#include "Engine.h"
#include "Cards.h"
#include "Wonders.hpp"
#include "CardGenerator.hpp"
#include <ctime>
#include <algorithm>

GameEngine::GameEngine(int count, int real)
{
	PlayerCount = count;
	RealPlayers = real;
}

void GameEngine::InitializeTheGame()
{
	if (PlayerCount <= 2 || PlayerCount > 7) throw std::invalid_argument("Invalid player count!");
	if (RealPlayers < 0 || RealPlayers > PlayerCount) throw std::invalid_argument("Invalid real player count!");


	std::vector<int> PlayerIndexes;
	for (int i = 0; i < PlayerCount; i++)
	{
		Players.push_back(Player());
		PlayerIndexes.push_back(i);
	}

	// randomly determine the positions of real players
	std::srand(std::time(0));
	std::random_shuffle(PlayerIndexes.begin(), PlayerIndexes.end());

	for (int Real = 0; Real < RealPlayers; Real++)
	{
		RealPlayersIndexes.push_back(PlayerIndexes.back());
		PlayerIndexes.pop_back();
	}

    // assign neighbours
	for (int j = 0; j < PlayerCount; j++)
	{
		// because c++ doesnt have proper modulo we have to use this weird formula instead
		Players[j].LeftNeighbour = std::make_shared<Player>(Players[((j - 1) % PlayerCount + PlayerCount) % PlayerCount]);
		Players[j].RightNeighbour = std::make_shared<Player>(Players[((j + 1) % PlayerCount + PlayerCount) % PlayerCount]);
	}

	
	// randomly assign wonders to players
	std::vector<int> WondersToDistribute = {  1, 2, 3, 4, 5, 6, 7 };

	std::srand(std::time(0)); // get random seed, or the shuffle will be the same every time
	std::random_shuffle(WondersToDistribute.begin(), WondersToDistribute.end());

	for (int l = 0; l < PlayerCount; l++)
	{
		Players[l].Wonder = std::move(GenerateWonder(WondersToDistribute[l]));
		Players[l].Wonder->InitialResource(Players[l]); // give the starting resource of the wonder to the player

		PlayersHands.push_back(std::vector<std::shared_ptr<BaseCard>>());
	}
}

void GameEngine::PresentCardsToPlayer(std::ostream &stream, Player &player, std::vector<std::shared_ptr<BaseCard>>& cards)
{
	std::map<std::shared_ptr<BaseCard>, std::vector<int>> CardPriceMap;
	std::vector<int> PlayableCardIndexes; // will contain the card indexes player CAN afford
	std::vector<int> UnplayableCardIndexes; // will contain the card indexes player CAN NOT afford
	bool CanAffordWonder = false;

	int index = 0;
	for (auto& card : cards)
	{
		auto cost = DetermineLowestBuyingCost(player, card); 

		if (cost[0] <= player.Gold) PlayableCardIndexes.push_back(index);
		else UnplayableCardIndexes.push_back(index);

		CardPriceMap.insert(std::make_pair(card, cost));
		index++;

	}

	// print affordable cards
	for (int PlayableIndex : PlayableCardIndexes)
	{
		auto Playable = cards[PlayableIndex];
		if (CardPriceMap[Playable][0] == 0) // doesnt' have to spend anything
		{
			stream << "(Index " << std::to_string(PlayableIndex) << ") -- You can afford " << Playable->CardName() << " for free." << std::endl;
		}
		else
		{
			stream << "(Index " << std::to_string(PlayableIndex) << ") -- You can afford " << Playable->CardName();
			stream << " for a cost of: " << std::to_string(CardPriceMap[Playable][0]);
			stream << std::endl;
		}
	}

	// print unaffordable cards
	for (int UnplayableIndex : UnplayableCardIndexes)
	{
		auto Unplayable = cards[UnplayableIndex];
		stream << "(Index " << std::to_string(UnplayableIndex) << ") -- You can not afford " << Unplayable->CardName() << "." << std::endl;
	}

	// determine if wonder can be played
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

	stream << std::endl;
	PrintPlayerStats(std::cout, player);
	// REPL loop
	while (true)
	{
		stream << "Avaliable commands: play X; discard X; wonder X; info X/wonder; stats left/right/me; exit. X is the index of the card." << std::endl;
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

std::vector<int> GameEngine::DetermineLowestBuyingCost(Player &player, std::shared_ptr<BaseCard> card)
{
	// most of the time players will have only one or two resource vectors, so performance should be OK
	// the rough cap of different resource vectors in base game is 16 + C (caravanserai + appropriate wonder)

	int MinimumCost = 1000; // the real cost won't ever be bigger, so it's safe
	int GoldPaidToLeft = 0;
	int GoldPaidToRight = 0;

	if (card->CanPlayerAffordThisForFree(player)) return { 0,0,0 };

	for (ResourceVector &PlayerResource : player.TradableResources)
	{
		ResourceVector ResourcesToBuy = card->CardCost - PlayerResource;

		// we need to loop over all possible combinations of neighbour's resources
		for (ResourceVector &LeftNeighbourResource : player.LeftNeighbour->TradableResources)
		{
			for (ResourceVector &RightNeighbourResource : player.RightNeighbour->TradableResources)
			{
				//int CostOfThisPair = 0; // how much will this pair cost us
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

					// if the total cost would be 0, then it would pass the CanAffordForFree test
					// so this purchase combination actually doesn't buy anything

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
	return { MinimumCost, GoldPaidToLeft, GoldPaidToRight};
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
	ScoredPoints += player.Gold / 3;
	return ScoredPoints;
}

int GameEngine::ScoreSciencePoints(Player &player)
{
	int ScoredPoints = 0;

	// find the symbol combination that gives most points
	for (ScienceVector &vector : player.ScienceVectors)
	{
		int VectorScore = 0;
		VectorScore += *std::min_element(vector.ScienceArray.begin(), vector.ScienceArray.end()) * 7; // 7 points for every set of symbols
		for (int i = 0; i <= 2; i++)
		{
			VectorScore += vector.ScienceArray[i] * vector.ScienceArray[i]; // N^2 points, where N is the number of a single symbol
		}

		if (VectorScore > ScoredPoints) ScoredPoints = VectorScore;
	}

	return ScoredPoints;
}

std::shared_ptr<BaseWonder> GameEngine::GenerateWonder(int WonderIndex)
{
	switch (WonderIndex)
	{
	case 1:
		return std::make_shared<Gizah>();
		break;

	case 2:
		return std::make_shared<Rhodos>();
		break;

	case 3:
		return std::make_shared<Alexandria>();
		break;

	case 4:
		return std::make_shared<Babylon>();
		break;

	case 5:
		return std::make_shared<Halikarnassos>();
		break;

	case 6:
		return std::make_shared<Ephesus>();
		break;

	case 7:
		return std::make_shared<Olympia>();
		break;

	default:
		
		throw std::exception("Index out of range!");
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

	stream << "Played cards: ";
	for (auto& card : player.PlayedCards)
	{
		stream << " " << card->CardName();
	}
	stream << std::endl;
	stream << "Scored points: " << std::to_string(ScorePlayerPoints(player)) << std::endl;
	stream << std::endl;

}

void GameEngine::ProcessSingleTurn(int CardRotation)
{
	
	// let every player pick a card.
	for (int Index = 0; Index < (int)Players.size(); Index++)
	{
		// check if the player is a real one. being real is hard.
		if (std::find(RealPlayersIndexes.begin(), RealPlayersIndexes.end(), Index) != RealPlayersIndexes.end())
		{ 
			PresentCardsToPlayer(std::cout, Players[Index], PlayersHands[Index]);
		}
		
		else PresentCardstoAI(Players[Index], PlayersHands[Index]);
	}

	// then buy and play the cards at the same time and process gold transactions
	for (auto& transaction : GoldTransactions)
	{
		DistributeGoldToNeighbours(transaction.first, *transaction.second);
	}

	for (auto& PlayedCard : PlayedCardsQueue)
	{
		PlayedCard.first->Play(*PlayedCard.second);
	}

	if (CardRotation == 1) std::rotate(PlayersHands.begin(), PlayersHands.begin() + 1, PlayersHands.end()); // pass the cards clockwise
	else std::rotate(PlayersHands.begin(), PlayersHands.end() - 1, PlayersHands.end()); // counterclockwise

	GoldTransactions.clear();
	PlayedCardsQueue.clear();
}

void GameEngine::PresentCardstoAI(Player& player, std::vector<std::shared_ptr<BaseCard>>& cards)
{
	std::vector<std::shared_ptr<BaseCard>> PlayableCards;

	// check what cards can be played
	for (auto& card : cards)
	{
		auto CardCost = DetermineLowestBuyingCost(player, card);
		if (CardCost[0] <= player.Gold)
		{
			PlayableCards.push_back(card);
		}
	}
	
	// check if wonder can be played
	if (player.Wonder->CurrentBuilding != nullptr)
	{
		if (DetermineLowestBuyingCost(player, player.Wonder->CurrentBuilding)[0] <= player.Gold)
		{
			PlayableCards.push_back(player.Wonder->CurrentBuilding);
		}
	}
	
	std::srand(std::time(0));
	std::random_shuffle(PlayableCards.begin(), PlayableCards.end());

	// play the first card
	if (PlayableCards.size() > 0)
	{
		if (PlayableCards.front()->Type != Wonder)
		{
			ProcessCardPurchase(PlayableCards.front(), PlayableCards.front(), player, cards);
		}
		else
		{
			ProcessCardPurchase(PlayableCards.front(), cards.front(), player, cards);
		}
	}
	else // can't play anything, so discarding
	{
		auto discard = std::make_shared<DiscardedCard>();
		ProcessCardPurchase(discard, cards.front(), player, cards);
	}
}

void GameEngine::DistributeGoldToNeighbours(std::vector<int> GoldToDistribute, Player& player)
{
	player.Gold -= GoldToDistribute[0];
	player.LeftNeighbour->Gold += GoldToDistribute[1];
	player.RightNeighbour->Gold += GoldToDistribute[2];
}

void GameEngine::ProcessCardPurchase(std::shared_ptr<BaseCard> CardToPlay, std::shared_ptr<BaseCard>CardToDiscard, Player& player, std::vector<std::shared_ptr<BaseCard>>& hand)
{

	GoldTransactions.push_back(std::make_pair(DetermineLowestBuyingCost(player, CardToPlay), &player));
	
	PlayedCardsQueue.push_back(std::make_pair(CardToPlay, &player));

	auto IndexToRemove = std::find(hand.begin(), hand.end(), CardToDiscard);
	if (IndexToRemove == hand.end()) throw new std::exception("Discarded card is not in player's hand!");
	hand.erase(IndexToRemove);


	if (CardToPlay->Type == Wonder)
	{
		player.Wonder->GetNextWonderBuilding();
	}

}

void GameEngine::PlayTheGame()
{
	InitializeTheGame();

	Generator CardGenerator;
	PlayersHands = CardGenerator.GenerateFirstAgeCards(PlayerCount);
	
	for (int turn = 0; turn < 6; turn++)
	{
		ProcessSingleTurn(1);
	}
	CalculateMilitaryFights(1);

	PlayersHands = CardGenerator.GenerateSecondAgeCards(PlayerCount);
	for (int turn = 0; turn < 6; turn++)
	{
		ProcessSingleTurn(0);
	}
	CalculateMilitaryFights(3);


	PlayersHands = CardGenerator.GenerateThirdAgeCards(PlayerCount);
	for (int turn = 0; turn < 6; turn++)
	{
		ProcessSingleTurn(1);
	}
	CalculateMilitaryFights(5);

	for (int index = 0; index < PlayerCount; index++)
	{
		std::cout << "------------------" << std::endl;
		DisplayPlayersPoints(std::cout, index);
	}
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

void GameEngine::DisplayPlayersPoints(std::ostream& stream, int PlayerIndex)
{
	stream << "Displaying scores for player number: " << std::to_string(PlayerIndex) << std::endl;
	stream << "Military score: " << std::to_string(Players[PlayerIndex].MilitaryLoses + Players[PlayerIndex].MilitaryWins) << std::endl;;
	stream << "Gold score: " << std::to_string(Players[PlayerIndex].Gold / 3) << std::endl;;
	int GovernmentScore = 0;
	int MerchantScore = 0;
	int GuildScore = 0;
	int ScienceScore = ScoreSciencePoints(Players[PlayerIndex]);
	int WonderScore = 0;
	for (auto card : Players[PlayerIndex].PlayedCards)
	{
		if (card->Type == Government) GovernmentScore += card->ScorePoints(Players[PlayerIndex]);
		if (card->Type == Merchant) MerchantScore += card->ScorePoints(Players[PlayerIndex]);
		if (card->Type == Guild) GuildScore += card->ScorePoints(Players[PlayerIndex]);
		if (card->Type == Wonder) WonderScore += card->ScorePoints(Players[PlayerIndex]);

	}

	stream << "Government score: " << std::to_string(GovernmentScore) << std::endl;
	stream << "Merchant score: " << std::to_string(MerchantScore) << std::endl;
	stream << "Guild score: " << std::to_string(GuildScore) << std::endl;
	stream << "Science score: " << std::to_string(ScienceScore) << std::endl;
	stream << "Wonder score: " << std::to_string(WonderScore) << std::endl;

	stream << "Total score: " << std::to_string(ScorePlayerPoints(Players[PlayerIndex])) << std::endl;

}