#pragma once
#include <array>

enum Resources { Wood, Clay, Iron, Stone, Glass, Cloth, Paper };
enum CardTypes {CommonResource, RareResource, Military, Merchant, Science, Government, Guild};
enum ScienceSymbols {Cog, Tableau, Compass};

class ResourceVector
{
public:
	ResourceVector(); // default empty constructor

    // returns true if all Resources in first vector are >= than those in the other
	bool operator>=(const ResourceVector& other);
    
    // returns the difference, but all negative numbers become zero
	ResourceVector operator-(const ResourceVector& other);
    
    // returns appropriate element from ResourcesArray
    int& operator[](int index);

	void ModifyResource(Resources resource, int change);

	std::array<int, 7> ResourcesArray;

};

class ScienceVector
{
public:
	ScienceVector();
	void ModifyResource(ScienceSymbols resource, int change);
	std::array<int, 3> ScienceArray;
};

