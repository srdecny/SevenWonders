#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "Player.h"
#include "stdafx.h"
#include "FirstAgeCards.h"



class GameEngine
{
public:
	GameEngine(int PlayerCount);
	~GameEngine();

	void PlayTheGame();

	int PlayerCount;
	std::vector<Player> Players;
	std::vector<std::vector<std::shared_ptr<BaseCard>>> PlayersHands;

	void InitializeTheGame();
	int ScorePlayerPoints(Player& player);

	// CardRotation  1 -> clockwise, 0 -> counterclockwise
	void ProcessSingleTurn(int CardRotation);

	void PresentCardsToPlayer(std::ostream& stream, Player& player, std::vector<std::shared_ptr<BaseCard>>& cards);
	void PresentCardstoAI(Player& player, std::vector<std::shared_ptr<BaseCard>>& cards);

	void PrintPlayerStats(std::ostream& stream, Player& player);

	bool PlayerCanAffordCard(Player& player, std::shared_ptr<BaseCard> card);

private:
	// find the cheapest way a player can buy a card
	std::vector<int> DetermineLowestBuyingCost(Player& player, std::shared_ptr<BaseCard> card);
	BaseWonder* GenerateWonder(int WonderIndex);
	int ScoreSciencePoints(Player& player);


	// this should be in process turn method
	std::vector<std::pair<std::vector<int>, Player*>> GoldTransactions;
	std::vector<std::pair<std::shared_ptr<BaseCard>, Player*>> PlayedCardsQueue;
	void DistributeGoldToNeighbours(std::vector<int> gold, Player& player);

	// adds card and gold transaction to queue and updates the hand
	void ProcessCardPurchase(std::shared_ptr<BaseCard> CardToPlay, std::shared_ptr<BaseCard> CardToDiscard, Player& player, std::vector<std::shared_ptr<BaseCard>>& hand);
	void DisplayPlayersPoints(std::ostream& stream, int PlayerIndex);
	void CalculateMilitaryFights(int PointsForWin);
};
