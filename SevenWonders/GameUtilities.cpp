#include "GameUtilities.h"
#include <string>

ResourceVector::ResourceVector()
{
	ResourcesArray = std::array<int, 7> {0, 0, 0, 0, 0, 0, 0};
}

bool ResourceVector::operator>=(const ResourceVector& other)
{
	for (int i = 0; i <= 6; i++)
	{
		if (ResourcesArray[i] < other.ResourcesArray[i]) return false;
	}
	return true;
}

ResourceVector ResourceVector::operator-(const ResourceVector & other)
{
	ResourceVector Result;

	for (int i = 0; i <= 6; i++)
	{
		Result.ResourcesArray[i] = ResourcesArray[i] - other.ResourcesArray[i];
		if (Result.ResourcesArray[i] < 0) Result.ResourcesArray[i] = 0;
	}

	return Result;
}

void ResourceVector::ModifyResource(Resources resource, int change)
{
	ResourcesArray[resource] += change;
}

int& ResourceVector::operator[](int index)
{
    return ResourcesArray[index];
}

ScienceVector::ScienceVector()
{
	ScienceArray = { 0,0,0 };
}

void ScienceVector::ModifyResource(ScienceSymbols symbol, int change)
{
	ScienceArray[symbol] += change;
}

std::string ResourceVector::PrintResourceVector()
{
	std::string result;
	result += "{ ";
	for (int i = 0; i < 7; i++)
	{
		result += ResourcesName[(Resources)i] + ": " + std::to_string(ResourcesArray[i]);
		if (i != 6) result += ", ";
	}
	
	result += " }";
	return result;
}


std::string ScienceVector::PrintScienceVector()
{
	std::string result;
	result += "{ ";
	for (int i = 0; i < 3; i++)
	{
		result += SymbolsName[(ScienceSymbols)i] + ": " + std::to_string(ScienceArray[i]);
		if (i != 2) result += ", ";
	}

	result += " }";
	return result;
}