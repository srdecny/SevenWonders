#include "Wonders.hpp"

BaseWonder::BaseWonder()
{
    return;
}
BaseWonder::~BaseWonder()
{
    return;
}

void PyramidesOfGizaA::InitialResource(Player &player)
{
    player.ModifyAvaliableResource(Stone, 1);
}

PyramidesOfGizaA::PyramidesOfGizaA()
{
    WonderLevel = 3;
    WonderBuildings = { Pyramides1A(), Pyramides2A(), Pyramides3A() };
}

Pyramides1A::Pyramides1A()
{
    CardCost.ModifyResource(Stone, 2);
}

int Pyramides1A::ScorePoints(Player& player)
{
    return 3;
}

Pyramides2A::Pyramides2A()
{
    CardCost.ModifyResource(Wood, 3);
}

int Pyramides2A::ScorePoints(Player& player)
{
    return 5;
};

Pyramides3A::Pyramides3A()
{
    CardCost.ModifyResource(Stone, 4);
}

int Pyramides3A::ScorePoints(Player &)
{
    return 7;
};




