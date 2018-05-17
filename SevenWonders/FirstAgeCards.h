#pragma once
#include "Cards.h"
#include "Player.h"

// RESOURCES
class ClayDeposit : public SingleResourceBuilding { public: ClayDeposit(); };
class IronMine : public SingleResourceBuilding { public: IronMine(); };
class LumberMill : public SingleResourceBuilding { public: LumberMill(); };
class StoneQuarry : public SingleResourceBuilding { public: StoneQuarry(); };

class PapyrusManufacture : public SingleResourceBuilding { public: PapyrusManufacture(); };
class WeavingMill : public SingleResourceBuilding { public: WeavingMill(); };
class Glassworks : public SingleResourceBuilding { public: Glassworks(); };

class Forestry : public MultipleResourceBuilding { public: Forestry(); };
class SurfaceMine : public MultipleResourceBuilding { public: SurfaceMine(); };
class DeepMine : public MultipleResourceBuilding { public: DeepMine(); };
class ForestCave : public MultipleResourceBuilding { public: ForestCave(); };
class ClayMine : public MultipleResourceBuilding { public: ClayMine(); };
class WoodedFoothills : public MultipleResourceBuilding { public: WoodedFoothills(); };

// MILITARY
class WoodenWall : public MilitaryBuilding { public: WoodenWall(); };
class WatchTower : public MilitaryBuilding { public: WatchTower(); };
class Barracks : public MilitaryBuilding { public: Barracks(); };

// GOVERNMENT
class Shrine : public  GovernmentBuilding { public: Shrine(); };
class Spa : public GovernmentBuilding { public: Spa(); };
class Theatre : public GovernmentBuilding { public: Theatre(); };
class PawnShop : public GovernmentBuilding { public: PawnShop(); };

// SCIENCE
class ScriberShop : public ScienceBuilding { public: ScriberShop(); };
class Aphotecary : public ScienceBuilding { public: Aphotecary(); };
class Workshop : public ScienceBuilding { public: Workshop(); };

// MERCHANT

class Pub : public MilitaryBuilding 
{
public:
	Pub();
	void CardEffect(Player& player) override;
};
class EasternMarket : public MilitaryBuilding 
{
public: 
	EasternMarket();
	void CardEffect(Player& player) override;
};
class WesternMarket : public MilitaryBuilding 
{
public:
	WesternMarket();
	void CardEffect(Player& player) override;
};
class Marketplace : public MilitaryBuilding 
{
public:
	Marketplace();
	void CardEffect(Player& player) override;
};



