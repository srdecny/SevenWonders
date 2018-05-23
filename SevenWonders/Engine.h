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
	GameEngine(int PlayerCount, int RealPlayers);
	void PlayTheGame();

private:

	// generates the players and their wonders
	void InitializeTheGame();

	int PlayerCount; // number of players in the game
	int RealPlayers; // number of human players
	std::vector<Player> Players;
	std::vector<std::vector<std::shared_ptr<BaseCard>>> PlayersHands;
	std::vector<int> RealPlayersIndexes;
	std::shared_ptr<BaseWonder> GenerateWonder(int WonderIndex); // used by InitializeTheGame()

	// CardRotation 1/0 - rotates the hands clockwise/counterclockwise
	// Presents the cards to players and process purchases
	void ProcessSingleTurn(int CardRotation);

	// [0] - total cost (including the GoldCost of the card), [1] - paid to left neighbour, [2] - paid to right neighbour
	std::vector<int> DetermineLowestBuyingCost(Player& player, std::shared_ptr<BaseCard> card);

	// contains REPL loop for player input
	void PresentCardsToPlayer(std::ostream& stream, Player& player, std::vector<std::shared_ptr<BaseCard>>& cards);
	// currently plays a random card if possible; discarding a card if not.
	void PresentCardstoAI(Player& player, std::vector<std::shared_ptr<BaseCard>>& cards);
	// distributes PointsForWin, comparing the Military power of players
	void CalculateMilitaryFights(int PointsForWin);

	// Gold transaction for purchasing resources and playing the cards is done simultaneously
	// these auxiliary vectors and functions are invoked after every turn
	std::vector<std::pair<std::vector<int>, Player*>> GoldTransactions;
	std::vector<std::pair<std::shared_ptr<BaseCard>, Player*>> PlayedCardsQueue;
	void DistributeGoldToNeighbours(std::vector<int> gold, Player& player);

	// hand MUST contain CardToDiscard. CardToPlay's card effect is invoked and the card is added to player's hand.
	void ProcessCardPurchase(std::shared_ptr<BaseCard> CardToPlay, std::shared_ptr<BaseCard> CardToDiscard, Player& player, std::vector<std::shared_ptr<BaseCard>>& hand);

	// auxiliary functions for displaying and computing player's scores.
	void DisplayPlayersPoints(std::ostream& stream, int PlayerIndex);
	void PrintPlayerStats(std::ostream& stream, Player& player);
	int ScorePlayerPoints(Player& player);
	int ScoreSciencePoints(Player& player);
};
