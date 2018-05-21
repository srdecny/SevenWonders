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
    virtual void InitialResource(Player& player) = 0;
	int CurrentLevel = 0;
    std::vector<std::shared_ptr<BaseCard>> WonderBuildings;
	std::shared_ptr<BaseCard> CurrentBuilding;
	std::string WonderName;

	void GetNextWonderBuilding();
};

class Gizah : public BaseWonder
{
public:
    void InitialResource(Player& player);
    Gizah();
};

class Rhodos : public BaseWonder
{
public:
	void InitialResource(Player& player);
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