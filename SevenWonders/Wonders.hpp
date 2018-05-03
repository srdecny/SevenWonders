#pragma once
#include "stdafx.h"
#include <stdio.h>
#include "Player.h"
#include "GameUtilities.h"
#include <vector>

class Player;

class BaseWonder
{
public:
    BaseWonder();
    ~BaseWonder();
    virtual void InitialResource(Player& player) = 0;
    int WonderLevel;
    std::vector<BaseCard> WonderBuildings;
};

class PyramidesOfGizaA : public BaseWonder
{
    void InitialResource(Player& player);
    PyramidesOfGizaA();
    ~PyramidesOfGizaA();
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

