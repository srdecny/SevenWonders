#pragma once
#include "FirstAgeCards.h"

class Generator
{
public:
	std::vector<std::vector<std::shared_ptr<BaseCard>>> GenerateFirstAgeCards(int Players);
};