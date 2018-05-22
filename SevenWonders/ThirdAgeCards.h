#pragma once
#include "Cards.h"


// MILITARY

class Circus : public MilitaryBuilding { public: Circus(); };
class Fortress : public MilitaryBuilding { public: Fortress(); };
class Armory : public MilitaryBuilding { public: Armory(); };
class Trebuchet : public MilitaryBuilding { public: Trebuchet(); };

// GOVERNMENT

class Palace : public GovernmentBuilding { public: Palace(); };
class TownHall : public GovernmentBuilding { public: TownHall(); };
class Senate : public GovernmentBuilding { public: Senate(); };
class Pantheon : public GovernmentBuilding { public: Pantheon(); };
class Gardens : public GovernmentBuilding { public: Gardens(); };

// MERCHANT

class TradingCompany : public MerchantBuilding
{
public:
	TradingCompany();
	std::string CardInfo() override;
	void CardEffect(Player& player) override;
	int ScorePoints(Player& player) override;
};

class Lighthouse : public MerchantBuilding
{
public:
	Lighthouse();
	std::string CardInfo() override;
	void CardEffect(Player& player) override;
	int ScorePoints(Player& player) override;
};

class Harbor : public MerchantBuilding
{
public:
	Harbor();
	std::string CardInfo() override;
	void CardEffect(Player& player) override;
	int ScorePoints(Player& player) override;
};

class Arena : public MerchantBuilding
{
public:
	Arena();
	std::string CardInfo() override;
	int ScorePoints(Player& player) override;
	void CardEffect(Player& player) override;
};

// SCIENCE

class StudyHall : public ScienceBuilding { public: StudyHall(); };
class Academy : public ScienceBuilding { public: Academy(); };
class University : public ScienceBuilding { public: University(); };
class Observatory : public ScienceBuilding { public: Observatory(); };
class Lodge : public ScienceBuilding { public: Lodge(); };

// GUILDS

// SINGLE TYPE SCORING GUILDS

class PhilosophersGuild : public GuildBuilding { public: PhilosophersGuild(); };
class JudgesGuild : public GuildBuilding { public: JudgesGuild(); };
class SpiesGuild : public GuildBuilding { public: SpiesGuild(); };
class WorkersGuild : public GuildBuilding { public: WorkersGuild(); };
class ArchitectsGuild : public GuildBuilding { public: ArchitectsGuild(); };
class CraftmansGuild : public GuildBuilding { public: CraftmansGuild(); };
class MerchantsGuild : public GuildBuilding { public: MerchantsGuild(); };

// OTHER GUILDS

class GamersGuild : public GuildBuilding
{
public:
	GamersGuild();
	int ScorePoints(Player& player) override;
	std::string CardInfo() override;
};

class WarlordsGuild : public GuildBuilding
{
public:
	WarlordsGuild();
	int ScorePoints(Player& player) override;
	std::string CardInfo() override;
};

class ResearchersGuild : public GuildBuilding
{
public:
	ResearchersGuild();
	int ScorePoints(Player& player) override { return 0; };
	void CardEffect(Player& player) override;
	std::string CardInfo() override;
};

class SailorsGuild : public GuildBuilding
{
public:
	SailorsGuild();
	int ScorePoints(Player& player) override;
	std::string CardInfo() override;
};

class BuildersGuild : public GuildBuilding
{
public:
	BuildersGuild();
	int ScorePoints(Player& player) override;
	std::string CardInfo() override;
};