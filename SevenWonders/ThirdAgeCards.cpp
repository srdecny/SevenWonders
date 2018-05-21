#pragma once
#include "ThirdAgeCards.h"
#include "Player.h"

// MILITARY

Circus::Circus()
{
	Power = 3;
	CardCost.ModifyResource(Stone, 3);
	CardCost.ModifyResource(Iron, 1);
	PrerequisiteCards.push_back(200); // Training Grounds
	PlayerCount = { 4, 5, 6 };
}

Fortress::Fortress()
{
	Power = 3;
	CardCost.ModifyResource(Iron, 3);
	CardCost.ModifyResource(Stone, 1);
	PrerequisiteCards.push_back(201); // Stone Wall
	PlayerCount = { 3, 7 };
}

Armory::Armory()
{
	Power = 3;
	CardCost.ModifyResource(Wood, 2);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Cloth, 1);
	PlayerCount = { 3, 4, 7 };
}

Trebuchet::Trebuchet()
{
	Power = 3;
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Clay, 3);
	PrerequisiteCards.push_back(203); // Laboratory
	PlayerCount = { 3, 5 };
}

// GOVERNMENT

Palace::Palace()
{
	Points = 8;
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Clay, 1);
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Cloth, 1);
	CardCost.ModifyResource(Paper, 1);
	PlayerCount = { 3,7 };
}

TownHall::TownHall()
{
	Points = 6;
	CardCost.ModifyResource(Stone, 2);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Glass, 2);
	PlayerCount = { 3, 5, 6 };
}

Senate::Senate()
{
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Wood, 2);
	PrerequisiteCards.push_back(205); //Library
	PlayerCount = { 3, 5 };
}

Pantheon::Pantheon()
{
	Points = 7;
	CardCost.ModifyResource(Clay, 2);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Paper, 1);
	CardCost.ModifyResource(Cloth, 1);
	PrerequisiteCards.push_back(206); // Temple
	PlayerCount = { 3,6 };
}

Gardens::Gardens()
{
	Points = 5;
	CardCost.ModifyResource(Clay, 2);
	CardCost.ModifyResource(Wood, 1);
	PrerequisiteCards.push_back(207); // Statue
	PlayerCount = { 3,4 };
}

// MERCHANT

TradingCompany::TradingCompany()
{
	CardCost.ModifyResource(Clay, 2);
	CardCost.ModifyResource(Paper, 1);
	PlayerCount = { 4, 6 };
}

std::string TradingCompany::CardInfo()
{
	return "This card gives you 2 Gold and 2 Victory points for every Rare resource card you have.";
}

int TradingCompany::ScorePoints(Player& player)
{
	int CardCount;
	for (auto card : player.PlayedCards)
	{
		if (card->Type = RareResource) CardCount++;
	}

	return CardCount * 2;
}

void TradingCompany::CardEffect(Player& player)
{
	player.Gold += ScorePoints(player);
}

Lighthouse::Lighthouse()
{
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Stone, 1);
	PrerequisiteCards.push_back(208); // Caravanserai
	PlayerCount = { 3, 6 };
}

std::string Lighthouse::CardInfo()
{
	return "This card gives you 1 Gold and 1 Victory point for every Merchant card you have";
}

int Lighthouse::ScorePoints(Player& player)
{
	int CardCount;
	for (auto card : player.PlayedCards)
	{
		if (card->Type = Merchant) CardCount++;
	}

	return CardCount;
}

void Lighthouse::CardEffect(Player& player)
{
	player.Gold += ScorePoints(player);
}

Harbor::Harbor()
{
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Cloth, 1);
	PrerequisiteCards.push_back(209); // Tribunal
	PlayerCount = { 3, 4 };
}

std::string Harbor::CardInfo()
{
	return "This card gives you 1 Gold and 1 Victory point for every Common resource card you have.";
}

int Harbor::ScorePoints(Player& player)
{
	int CardCount;
	for (auto card : player.PlayedCards)
	{
		if (card->Type = CommonResource) CardCount++;
	}

	return CardCount;
}

void Harbor::CardEffect(Player& player)
{
	player.Gold += ScorePoints(player);
}

Arena::Arena()
{
	CardCost.ModifyResource(Stone, 2);
	CardCost.ModifyResource(Iron, 1);
	PrerequisiteCards.push_back(210); // Infirmary
	PlayerCount = { 3, 5, 7 };
}

std::string Arena::CardInfo()
{
	return "This card gives you 3 Gold and 1 Victory point for every Wonder level you built.";
}

int Arena::ScorePoints(Player& player)
{
	int CardCount;
	for (auto card : player.PlayedCards)
	{
		if (card->Type = Wonder) CardCount++;
	}

	return CardCount;
}

void Arena::CardEffect(Player& player)
{
	player.Gold += ScorePoints(player) * 3;
}

// SCIENCE

StudyHall::StudyHall()
{
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Cloth, 1);
	Symbol = Cog;
	PrerequisiteCards.push_back(203); // Laboratory
	PlayerCount = { 3, 7 };
}

University::University()
{
	CardCost.ModifyResource(Wood, 2);
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Paper, 1);
	Symbol = Tableau;
	PrerequisiteCards.push_back(205); // Library
	PlayerCount = { 3, 4 };
}

Academy::Academy()
{
	CardCost.ModifyResource(Stone, 3);
	CardCost.ModifyResource(Glass, 1);
	Symbol = Tableau;
	PrerequisiteCards.push_back(211); // School
	PlayerCount = { 3, 7 };
}

StudyHall::StudyHall()
{
	CardCost.ModifyResource(Wood, 1);
	CardCost.ModifyResource(Paper, 1);
	CardCost.ModifyResource(Cloth, 1);
	Symbol = Cog;
	PrerequisiteCards.push_back(211); // School
	PlayerCount = { 3, 5 };
}

Lodge::Lodge()
{
	CardCost.ModifyResource(Clay, 2);
	CardCost.ModifyResource(Paper, 1);
	CardCost.ModifyResource(Cloth, 1);
	Symbol = Compass;
	PrerequisiteCards.push_back(210); // Infirmary
	PlayerCount = { 3, 6 };
}

// GUILDS

// SINGLE TYPE SCORING GUILDS

PhilosophersGuild::PhilosophersGuild()
{
	CardCost.ModifyResource(Clay, 3);
	CardCost.ModifyResource(Paper, 1);
	CardCost.ModifyResource(Cloth, 1);
	ScoringType = Science;
	PointMultiplier = 1;
}

JudgesGuild::JudgesGuild()
{
	CardCost.ModifyResource(Wood, 3);
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Cloth, 1);
	ScoringType = Government;
	PointMultiplier = 1;
}

SpiesGuild::SpiesGuild()
{
	CardCost.ModifyResource(Clay, 3);
	CardCost.ModifyResource(Glass, 1);
	ScoringType = Military;
	PointMultiplier = 1;
}

WorkersGuild::WorkersGuild()
{
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Clay, 3);
	CardCost.ModifyResource(Wood, 1);
	ScoringType = CommonResource;
	PointMultiplier = 1;
}

ArchitectsGuild::ArchitectsGuild()
{
	CardCost.ModifyResource(Iron, 3);
	CardCost.ModifyResource(Paper, 1);
	CardCost.ModifyResource(Clay, 1);
	CardCost.ModifyResource(Cloth, 1);
	ScoringType = Guild;
	PointMultiplier = 3;
}

CraftmansGuild::CraftmansGuild()
{
	CardCost.ModifyResource(Stone, 2);
	CardCost.ModifyResource(Iron, 2);
	ScoringType = RareResource;
	PointMultiplier = 2;
}

MerchantsGuild::MerchantsGuild()
{
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Cloth, 1);
	CardCost.ModifyResource(Paper, 1);
	ScoringType = Merchant;
	PointMultiplier = 1;
}

// OTHER GUILDS

GamersGuild::GamersGuild()
{
	CardCost.ModifyResource(Iron, 1);
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Clay, 1);
	CardCost.ModifyResource(Wood, 1);
}

std::string GamersGuild::CardInfo()
{
	return "This card gives you 1 Victory point for every 3 Gold you have.";
}

int GamersGuild::ScorePoints(Player& player)
{
	return player.Gold / 3;
}

WarlordsGuild::WarlordsGuild()
{
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Stone, 1);
	CardCost.ModifyResource(Cloth, 1);
}

std::string WarlordsGuild()
{
	return "This card gives you 1 Victory point for each time your neighbours were defeated in Military combat.";
}

int WarlordsGuild::ScorePoints(Player& player)
{
	// the losses are negative ints
	return -1 * (player.LeftNeighbour->MilitaryLoses + player.RightNeighbour->MilitaryLoses)
}

ResearchersGuild::ResearchersGuild()
{
	CardCost.ModifyResource(Wood, 2);
	CardCost.ModifyResource(Iron, 2);
	CardCost.ModifyResource(Paper, 1);
}

std::string ResearchersGuild::CardInfo()
{
	return "This card provides any one Research symbol at a given time.";
}

void ResearchersGuild::CardEffect(Player& player)
{
	std::vector<ScienceVector> NewResources;
	std::vector<ScienceSymbols> ProducedSymbols = { Tableau, Cog, Compass };

	for (auto OldVector : player.ScienceVectors)
	{
		for (ScienceSymbols symbol : ProducedSymbols)
		{
			auto NewVector = ScienceVector(OldVector);
			NewVector.ModifyResource(symbol, 1);
			NewResources.push_back(NewVector);
		}
	}

	player.ScienceVectors.clear();

	for (auto NewVector : NewResources)
	{
		player.ScienceVectors.push_back(NewVector);
	}
}

SailorsGuild::SailorsGuild()
{
	CardCost.ModifyResource(Wood, 3);
	CardCost.ModifyResource(Glass, 1);
	CardCost.ModifyResource(Paper, 1);
}

std::string SailorsGuild()
{
	return "This card gives you 1 point for every Common Resource, Rare Resource and Guild cards you have.";
}

int SailorsGuild::ScorePoints(Player& player)
{
	int CardCount = 0;
	for (auto card : player.PlayedCards)
	{
		if (card->Type == CommonResource) CardCount++;
		if (card->Type == RareResource) CardCount++;
		if (card->Type == Guild) CardCount++;
	}

	return CardCount;
}