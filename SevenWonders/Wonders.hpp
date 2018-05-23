#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include "GameUtilities.h"
#include "Cards.h"


class Player;


class BaseWonder
{
public:
    BaseWonder();
	~BaseWonder();
    void InitialResource(Player& player);
	int CurrentLevel = 0;
    std::vector<std::shared_ptr<BaseCard>> WonderBuildings;
	std::shared_ptr<BaseCard> CurrentBuilding; // THIS CAN BE A NULLPTR!
	std::string WonderName;
	void GetNextWonderBuilding();

	Resources StartingResource;
};

class Gizah : public BaseWonder
{
public:
    Gizah();
};

class Rhodos : public BaseWonder
{
public:
	Rhodos();
};

class BaseFirstStage : public WonderBuilding
{
public:
	BaseFirstStage();
	std::string CardInfo() override;
};

class BaseThirdStage : public WonderBuilding
{
public:
	BaseThirdStage();
	std::string CardInfo() override;
};

class GizahSecondStage : public WonderBuilding
{
public:
	GizahSecondStage();
	std::string CardInfo() override;
};

class RhodosSecondStage : public WonderBuilding
{
public:
	RhodosSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Alexandria : public BaseWonder
{
public:
	Alexandria();
};

class AlexandriaSecondStage : public WonderBuilding
{
public:
	AlexandriaSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Babylon : public BaseWonder
{
public:
	Babylon();
};

class BabylonSecondStage : public WonderBuilding
{
public:
	BabylonSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;

};

class Ephesus : public BaseWonder
{
public:
	Ephesus();
};

class EphesusSecondStage : public WonderBuilding
{
public:
	EphesusSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};


class Olympia : public BaseWonder
{
public:
	Olympia();
};

class OlympiaSecondStage : public WonderBuilding
{
public:
	OlympiaSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Halikarnassos : public BaseWonder
{
public:
	Halikarnassos();
};

class HalikarnassosSecondStage : public WonderBuilding
{
public:
	HalikarnassosSecondStage();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};
