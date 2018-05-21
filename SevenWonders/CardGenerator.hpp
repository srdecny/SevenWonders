#pragma once
#include "FirstAgeCards.h"
#include "SecondAgeCards.h"
#include "ThirdAgeCards.h"

class Generator
{
public:
	std::vector<std::vector<std::shared_ptr<BaseCard>>> GenerateFirstAgeCards(int Players);
	std::vector<std::vector<std::shared_ptr<BaseCard>>> GenerateSecondAgeCards(int Players);
	std::vector<std::vector<std::shared_ptr<BaseCard>>> GenerateThirdAgeCards(int Players);

private:
	std::vector<std::vector<std::shared_ptr<BaseCard>>> GenerateHands(std::vector<std::shared_ptr<BaseCard>> cards, int Players);
};