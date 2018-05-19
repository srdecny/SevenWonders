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
	GameEngine();
	~GameEngine();

	std::vector<Player> Players;
	std::vector<std::vector<std::shared_ptr<BaseCard>>> PlayersHands;

	void InitializeTheGame(int PlayerCount);
	int ScorePlayerPoints(Player& player);

	void ProcessSingleTurn();

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
	std::vector<int> GoldTransactions;
	void ClearGoldTransactions();

	std::vector<std::pair<std::shared_ptr<BaseCard>, int>> PlayedCardsQueue;
};
