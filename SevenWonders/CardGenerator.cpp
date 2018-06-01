#pragma once
#include "stdafx.h"
#include "CardGenerator.hpp"
#include <ctime>

 std::vector<std::vector<std::shared_ptr<BaseCard>>> Generator::GenerateFirstAgeCards(int Players)
{
	std::vector<std::shared_ptr<BaseCard>> CardPool;
	CardPool.push_back(std::make_shared<ClayDeposit>());
	CardPool.push_back(std::make_shared<IronMine>());
	CardPool.push_back(std::make_shared<LumberMill>());
	CardPool.push_back(std::make_shared<StoneQuarry>());

	CardPool.push_back(std::make_shared<PapyrusManufacture>());
	CardPool.push_back(std::make_shared<WeavingMill>());
	CardPool.push_back(std::make_shared<Glassworks>());

	CardPool.push_back(std::make_shared<Forestry>());
	CardPool.push_back(std::make_shared<SurfaceMine>());
	CardPool.push_back(std::make_shared<DeepMine>());
	CardPool.push_back(std::make_shared<ForestCave>());
	CardPool.push_back(std::make_shared<ClayMine>());
	CardPool.push_back(std::make_shared<WoodedFoothills>());

	CardPool.push_back(std::make_shared<WoodenWall>());
	CardPool.push_back(std::make_shared<WatchTower>());
	CardPool.push_back(std::make_shared<Barracks>());

	CardPool.push_back(std::make_shared<Shrine>());
	CardPool.push_back(std::make_shared<Spa>());
	CardPool.push_back(std::make_shared<Theatre>());
	CardPool.push_back(std::make_shared<PawnShop>());

	CardPool.push_back(std::make_shared<ScriberShop>());
	CardPool.push_back(std::make_shared<Aphotecary>());
	CardPool.push_back(std::make_shared<Workshop>());

	CardPool.push_back(std::make_shared<Pub>());
	CardPool.push_back(std::make_shared<EasternMarket>());
	CardPool.push_back(std::make_shared<WesternMarket>());
	CardPool.push_back(std::make_shared<Marketplace>());

	return GenerateHands(CardPool, Players);

}

 std::vector<std::vector<std::shared_ptr<BaseCard>>> Generator::GenerateSecondAgeCards(int Players)
 {
	 std::vector<std::shared_ptr<BaseCard>> CardPool;

	 CardPool.push_back(std::make_shared<ClayFactory>());
	 CardPool.push_back(std::make_shared<StoneFactory>());
	 CardPool.push_back(std::make_shared<IronFactory>());
	 CardPool.push_back(std::make_shared<WoodFactory>());

	 CardPool.push_back(std::make_shared<SecondPapyrusManufacture>());
	 CardPool.push_back(std::make_shared<SecondWeavingMill>());
	 CardPool.push_back(std::make_shared<SecondGlassworks>());
	
	 CardPool.push_back(std::make_shared<StoneWall>());
	 CardPool.push_back(std::make_shared<Stables>());
	 CardPool.push_back(std::make_shared<Archery>());
	 CardPool.push_back(std::make_shared<TrainingGrounds>());

	 CardPool.push_back(std::make_shared<Statue>());
	 CardPool.push_back(std::make_shared<Aqueduct>());
	 CardPool.push_back(std::make_shared<Temple>());
	 CardPool.push_back(std::make_shared<CourtHouse>());

	 CardPool.push_back(std::make_shared<Caravanserai>());
	 CardPool.push_back(std::make_shared<Tribunal>());
	 CardPool.push_back(std::make_shared<Vineyard>());
	 CardPool.push_back(std::make_shared<Bazaar>());

	 CardPool.push_back(std::make_shared<Library>());
	 CardPool.push_back(std::make_shared<Laboratory>());
	 CardPool.push_back(std::make_shared<School>());
	 CardPool.push_back(std::make_shared<Infirmary>());

	 return GenerateHands(CardPool, Players);

 }

 std::vector<std::vector<std::shared_ptr<BaseCard>>> Generator::GenerateThirdAgeCards(int Players)
 {
	 std::vector<std::shared_ptr<BaseCard>> GuildPool;

	 GuildPool.push_back(std::make_shared<PhilosophersGuild>());
	 GuildPool.push_back(std::make_shared<JudgesGuild>());
	 GuildPool.push_back(std::make_shared<SpiesGuild>());
	 GuildPool.push_back(std::make_shared<WorkersGuild>());
	 GuildPool.push_back(std::make_shared<ArchitectsGuild>());
	 GuildPool.push_back(std::make_shared<CraftmansGuild>());
	 GuildPool.push_back(std::make_shared<MerchantsGuild>());

	 GuildPool.push_back(std::make_shared<GamersGuild>());
	 GuildPool.push_back(std::make_shared<WarlordsGuild>());
	 GuildPool.push_back(std::make_shared<ResearchersGuild>());
	 GuildPool.push_back(std::make_shared<SailorsGuild>());
	 GuildPool.push_back(std::make_shared<BuildersGuild>());

	 std::srand(std::time(0));
	 std::random_shuffle(GuildPool.begin(), GuildPool.end());


	 std::vector<std::shared_ptr<BaseCard>> CardPool;

	 // amount of guilds per game = number of player + 2
	 for (int i = 0; i < Players + 2; i++)
	 {
		 CardPool.push_back(GuildPool.back());
		 GuildPool.pop_back();
	 }

	 CardPool.push_back(std::make_shared<Circus>());
	 CardPool.push_back(std::make_shared<Fortress>());
	 CardPool.push_back(std::make_shared<Armory>());
	 CardPool.push_back(std::make_shared<Trebuchet>());

	 CardPool.push_back(std::make_shared<Palace>());
	 CardPool.push_back(std::make_shared<TownHall>());
	 CardPool.push_back(std::make_shared<Senate>());
	 CardPool.push_back(std::make_shared<Pantheon>());
	 CardPool.push_back(std::make_shared<Gardens>());

	 CardPool.push_back(std::make_shared<TradingCompany>());
	 CardPool.push_back(std::make_shared<Lighthouse>());
	 CardPool.push_back(std::make_shared<Harbor>());
	 CardPool.push_back(std::make_shared<Arena>());

	 CardPool.push_back(std::make_shared<StudyHall>());
	 CardPool.push_back(std::make_shared<Academy>());
	 CardPool.push_back(std::make_shared<University>());
	 CardPool.push_back(std::make_shared<Observatory>());
	 CardPool.push_back(std::make_shared<Lodge>());

	 return GenerateHands(CardPool, Players);

 }

 std::vector<std::vector<std::shared_ptr<BaseCard>>> Generator::GenerateHands(std::vector<std::shared_ptr<BaseCard>> cards, int Players)
 {
	 std::vector<std::shared_ptr<BaseCard>> SortedCards;
	 for (auto card : cards)
	 {
		 for (int PlayerCount : card->PlayerCount)
		 {
			 if (PlayerCount <= Players)
			 {
				 SortedCards.push_back(card);
			 }
		 }
	 }

	 std::srand(std::time(0)); // get random seed, or the shuffle will be the same every time
	 std::random_shuffle(SortedCards.begin(), SortedCards.end());

	 std::vector<std::vector<std::shared_ptr<BaseCard>>> PlayersHands;

	 for (int player = 0; player < Players; player++)
	 {
		 std::vector<std::shared_ptr<BaseCard>> Hand;

		 for (int i = 0; i < 7; i++)
		 {
			 Hand.push_back(SortedCards.back());
			 SortedCards.pop_back();
		 }
		 PlayersHands.push_back(Hand);

	 }

	 return PlayersHands;
 }