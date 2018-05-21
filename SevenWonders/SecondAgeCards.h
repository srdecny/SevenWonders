#pragma once
#include "Cards.h"

// RESOURCES

class ClayFactory : public SingleResourceBuilding { public: ClayFactory(); };
class StoneFactory : public SingleResourceBuilding { public: StoneFactory(); };
class IronFactory : public SingleResourceBuilding { public: IronFactory(); };
class WoodFactory : public SingleResourceBuilding { public: WoodFactory(); };

// can't reuse buildings from first age, because they have different PlayerCount
class SecondPapyrusManufacture : public SingleResourceBuilding { public: SecondPapyrusManufacture(); };
class SecondWeavingMill : public SingleResourceBuilding { public: SecondWeavingMill(); };
class SecondGlassworks : public SingleResourceBuilding { public: SecondGlassworks(); };

// MILITARY

class StoneWall : public MilitaryBuilding { public: StoneWall(); };
class Stables : public MilitaryBuilding { public: Stables(); };
class Archery : public MilitaryBuilding { public: Archery(); };
class TrainingGrounds : public MilitaryBuilding { public: TrainingGrounds(); };

// GOVERNMENT

class Statue : public GovernmentBuilding { public: Statue(); };
class Aqueduct : public GovernmentBuilding { public: Aqueduct(); };
class Temple : public GovernmentBuilding { public: Temple(); };
class CourtHouse : public GovernmentBuilding { public: CourtHouse(); };

// MERCHANT

class Caravanserai : public MerchantBuilding
{
public:
	Caravanserai();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Tribunal : public MerchantBuilding
{
public:
	Tribunal();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Vineyard : public MerchantBuilding
{
public:
	Vineyard();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class Bazaar : public MerchantBuilding
{
public:
	Bazaar();
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};


// SCIENCE

class Library : public ScienceBuilding { public: Library(); };
class Laboratory : public ScienceBuilding { public: Laboratory(); };
class School : public ScienceBuilding { public: School(); };
class Infirmary : public ScienceBuilding { public: Infirmary(); };