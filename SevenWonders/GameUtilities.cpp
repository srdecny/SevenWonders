#include "GameUtilities.h"

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

