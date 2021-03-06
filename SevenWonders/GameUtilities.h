#pragma once
#include <array>
#include <map>

enum Resources { Wood, Clay, Iron, Stone, Glass, Cloth, Paper };
enum CardTypes {CommonResource, RareResource, Military, Merchant, Science, Government, Guild, Wonder};
enum ScienceSymbols {Cog, Tableau, Compass};

static std::map<Resources, std::string> ResourcesName = { {Wood, "Wood"}, {Clay, "Clay"}, { Iron, "Iron" }, { Stone, "Stone" }, { Glass, "Glass" }, { Cloth, "Cloth" }, { Paper, "Paper"} };
static std::map<ScienceSymbols, std::string> SymbolsName = { {Cog, "Cog"}, {Tableau, "Tableau"}, {Compass, "Compass"} };
static std::map<CardTypes, std::string> CardTypesName = { {CommonResource, "CommonResource"},{ RareResource, "RareResource" },{ Military, "Military" },{ Merchant, "Merchant" },{ Science, "Science" },{ Government, "Government" },{ Guild, "Guild" },{ Wonder, "Wonder" } };

class ResourceVector
{
public:
	ResourceVector();

    // returns true if all Resources in first vector are >= than those in the other
	bool operator>=(const ResourceVector& other);
    
    // returns the difference, but all negative numbers become zero
	ResourceVector operator-(const ResourceVector& other);
    
    // returns appropriate element from ResourcesArray
    int& operator[](int index);

	void ModifyResource(Resources resource, int change);
	std::string PrintResourceVector();
	std::array<int, 7> ResourcesArray;

};

class ScienceVector
{
public:
	ScienceVector();
	void ModifyResource(ScienceSymbols resource, int change);
	std::array<int, 3> ScienceArray;

	std::string PrintScienceVector();
};



