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
    int WonderLevel;
	int CurrentLevel = 0;
    std::vector<BaseCard> WonderBuildings;
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
};

class BaseThirdStage : public WonderBuilding
{
public:
	BaseThirdStage();
};

class GizahSecondStage : public WonderBuilding
{
public:
	GizahSecondStage();
};

class RhodosSecondStage : public WonderBuilding
{
public:
	RhodosSecondStage();
	void CardEffect(Player& player) override;
};