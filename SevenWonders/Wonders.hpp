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

class Pyramides1 : public BaseCard
{
public:
    Pyramides1();
    int ScorePoints(Player& player);
};

class Pyramides2 : public BaseCard
{
public:
    Pyramides2();
    int ScorePoints(Player& player);
};

class Pyramides3 : public BaseCard
{
public:
    Pyramides3();
    int ScorePoints(Player& player);
};

class Rhodos : public BaseWonder
{
public:
	void InitialResource(Player& player);
	Rhodos();
};

class Rhodos1 : public BaseCard
{
public:
	Rhodos1();
	int ScorePoints(Player& player);
};

class Rhodos2 : public BaseCard
{
public:
	Rhodos2();
	void CardEffect(Player& player);
};

class Rhodos3 : public BaseCard
{
public:
	Rhodos3();
	int ScorePoints(Player& player);
};