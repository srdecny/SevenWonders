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

class PyramidesOfGizaA : public BaseWonder
{
    void InitialResource(Player& player);
    PyramidesOfGizaA();
};

class Pyramides1A : public BaseCard
{
public:
    Pyramides1A();
    int ScorePoints(Player& player);
};

class Pyramides2A : public BaseCard
{
public:
    Pyramides2A();
    int ScorePoints(Player& player);
};

class Pyramides3A : public BaseCard
{
public:
    Pyramides3A();
    int ScorePoints(Player& player);
};

