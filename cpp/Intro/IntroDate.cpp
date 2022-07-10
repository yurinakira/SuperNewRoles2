//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "IntroDate.h"
#include "../TranslateDate.h"
#include "../Roles/RoleHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Intro
{

std::vector<IntroDate*> IntroDate::IntroDatas;
std::unordered_map<RoleId, IntroDate*> IntroDate::IntroDatasCache;
std::vector<IntroDate*> IntroDate::GhostRoleDatas;

	IntroDate::IntroDate(const std::wstring &NameKey, Color *color, short TitleNum, CustomRPC::RoleId RoleId, TeamRoleType team, bool IsGhostRole)
	{
		this->color = color;
		this->NameKey = NameKey;
		this->Name = ModTranslation::getString(NameKey + L"Name");
		this->RoleId = RoleId;
		this->TitleNum = TitleNum;
		this->TitleDesc = GetTitle(NameKey, TitleNum);
		this->Description = ModTranslation::getString(NameKey + L"Description");
		this->Team = team;
		this->IsGhostRole = IsGhostRole;

		if (IsGhostRole)
		{
			GhostRoleDatas.push_back(this);
		}
		IntroDatas.push_back(this);
	}

	IntroDate *IntroDate::GetIntroDate(RoleId RoleId, PlayerControl *p)
	{
		if (RoleId == RoleId::DefaultRole)
		{
			if (p != nullptr && SuperNewRoles::RoleHelpers::isImpostor(p))
			{
				return ImpostorIntro;
			}
			else
			{
				return CrewmateIntro;
			}
		}
		try
		{
			return IntroDatasCache[RoleId];
		}
		catch (...)
		{
			auto data = IntroDatas.FirstOrDefault([&] (_)
			{
				return _->RoleId == RoleId;
			});
			if (data == nullptr)
			{
				data = CrewmateIntro;
			}
			IntroDatasCache[RoleId] = data;
			return data;
		}
	}

	CustomRoleOption *IntroDate::GetOption(RoleId roleId)
	{
		auto option = CustomRoleOption::RoleOptions.FirstOrDefault([&] (_)
		{
			return _->RoleId == roleId;
		});
		return option;
	}

	std::wstring IntroDate::GetTitle(const std::wstring &name, short num)
	{
		System::Random *r1 = new System::Random();

		delete r1;
		return ModTranslation::getString(name + L"Title" + std::to_wstring(r1->Next(1, num + 1)));
	}

IntroDate *IntroDate::CrewmateIntro = new IntroDate(L"CrewMate", Color::white, 1, CustomRPC::RoleId::DefaultRole);
IntroDate *IntroDate::ImpostorIntro = new IntroDate(L"Impostor", RoleClass::ImpostorRed, 1, CustomRPC::RoleId::DefaultRole, TeamRoleType::Impostor);
IntroDate *IntroDate::SoothSayerIntro = new IntroDate(L"SoothSayer", RoleClass::SoothSayer::color, 1, CustomRPC::RoleId::SoothSayer);
IntroDate *IntroDate::JesterIntro = new IntroDate(L"Jester", RoleClass::Jester::color, 1, CustomRPC::RoleId::Jester, TeamRoleType::Neutral);
IntroDate *IntroDate::LighterIntro = new IntroDate(L"Lighter", RoleClass::Lighter::color, 1, CustomRPC::RoleId::Lighter);
IntroDate *IntroDate::EvilLighterIntro = new IntroDate(L"EvilLighter", RoleClass::EvilLighter::color, 2, CustomRPC::RoleId::EvilLighter, TeamRoleType::Impostor);
IntroDate *IntroDate::EvilScientist = new IntroDate(L"EvilScientist", RoleClass::EvilScientist::color, 2, CustomRPC::RoleId::EvilScientist, TeamRoleType::Impostor);
IntroDate *IntroDate::SheriffIntro = new IntroDate(L"Sheriff", RoleClass::Sheriff::color, 2, CustomRPC::RoleId::Sheriff);
IntroDate *IntroDate::MeetingSheriffIntro = new IntroDate(L"MeetingSheriff", RoleClass::MeetingSheriff::color, 4, CustomRPC::RoleId::MeetingSheriff);
IntroDate *IntroDate::JackalIntro = new IntroDate(L"Jackal", RoleClass::Jackal::color, 3, CustomRPC::RoleId::Jackal, TeamRoleType::Neutral);
IntroDate *IntroDate::SidekickIntro = new IntroDate(L"Sidekick", RoleClass::Jackal::color, 1, CustomRPC::RoleId::Sidekick, TeamRoleType::Neutral);
IntroDate *IntroDate::TeleporterIntro = new IntroDate(L"Teleporter", RoleClass::Teleporter::color, 2, CustomRPC::RoleId::Teleporter, TeamRoleType::Impostor);
IntroDate *IntroDate::SpiritMediumIntro = new IntroDate(L"SpiritMedium", RoleClass::SpiritMedium::color, 1, CustomRPC::RoleId::SpiritMedium);
IntroDate *IntroDate::SpeedBoosterIntro = new IntroDate(L"SpeedBooster", RoleClass::SpeedBooster::color, 2, CustomRPC::RoleId::SpeedBooster);
IntroDate *IntroDate::EvilSpeedBoosterIntro = new IntroDate(L"EvilSpeedBooster", RoleClass::EvilSpeedBooster::color, 4, CustomRPC::RoleId::EvilSpeedBooster, TeamRoleType::Impostor);
IntroDate *IntroDate::TaskerIntro = new IntroDate(L"Tasker", RoleClass::Tasker::color, 2, CustomRPC::RoleId::Tasker, TeamRoleType::Impostor);
IntroDate *IntroDate::DoorrIntro = new IntroDate(L"Doorr", RoleClass::Doorr::color, 2, CustomRPC::RoleId::Doorr);
IntroDate *IntroDate::EvilDoorrIntro = new IntroDate(L"EvilDoorr", RoleClass::EvilDoorr::color, 3, CustomRPC::RoleId::EvilDoorr, TeamRoleType::Impostor);
IntroDate *IntroDate::ShielderIntro = new IntroDate(L"Shielder", RoleClass::Shielder::color, 3, CustomRPC::RoleId::Shielder);
IntroDate *IntroDate::FreezerIntro = new IntroDate(L"Freezer", RoleClass::Freezer::color, 3, CustomRPC::RoleId::Freezer, TeamRoleType::Impostor);
IntroDate *IntroDate::SpeederIntro = new IntroDate(L"Speeder", RoleClass::Speeder::color, 2, CustomRPC::RoleId::Speeder, TeamRoleType::Impostor);
IntroDate *IntroDate::GuesserIntro = new IntroDate(L"Guesser", RoleClass::Guesser::color, 2, CustomRPC::RoleId::Guesser);
IntroDate *IntroDate::EvilGuesserIntro = new IntroDate(L"EvilGuesser", RoleClass::EvilGuesser::color, 1, CustomRPC::RoleId::EvilGuesser, TeamRoleType::Impostor);
IntroDate *IntroDate::VultureIntro = new IntroDate(L"Vulture", RoleClass::Vulture::color, 1, CustomRPC::RoleId::Vulture, TeamRoleType::Neutral);
IntroDate *IntroDate::NiceScientistIntro = new IntroDate(L"NiceScientist", RoleClass::NiceScientist::color, 2, CustomRPC::RoleId::NiceScientist);
IntroDate *IntroDate::ClergymanIntro = new IntroDate(L"Clergyman", RoleClass::Clergyman::color, 2, CustomRPC::RoleId::Clergyman);
IntroDate *IntroDate::MadMateIntro = new IntroDate(L"MadMate", RoleClass::MadMate::color, 1, CustomRPC::RoleId::MadMate);
IntroDate *IntroDate::BaitIntro = new IntroDate(L"Bait", RoleClass::Bait::color, 1, CustomRPC::RoleId::Bait);
IntroDate *IntroDate::HomeSecurityGuardIntro = new IntroDate(L"HomeSecurityGuard", RoleClass::HomeSecurityGuard::color, 1, CustomRPC::RoleId::HomeSecurityGuard);
IntroDate *IntroDate::StuntManIntro = new IntroDate(L"StuntMan", RoleClass::StuntMan::color, 1, CustomRPC::RoleId::StuntMan);
IntroDate *IntroDate::MovingIntro = new IntroDate(L"Moving", RoleClass::Moving::color, 1, CustomRPC::RoleId::Moving);
IntroDate *IntroDate::OpportunistIntro = new IntroDate(L"Opportunist", RoleClass::Opportunist::color, 2, CustomRPC::RoleId::Opportunist, TeamRoleType::Neutral);
IntroDate *IntroDate::NiceGamblerIntro = new IntroDate(L"NiceGambler", RoleClass::NiceGambler::color, 1, CustomRPC::RoleId::NiceGambler);
IntroDate *IntroDate::EvilGamblerIntro = new IntroDate(L"EvilGambler", RoleClass::EvilGambler::color, 1, CustomRPC::RoleId::EvilGambler, TeamRoleType::Impostor);
IntroDate *IntroDate::BestfalsechargeIntro = new IntroDate(L"Bestfalsecharge", RoleClass::Bestfalsecharge::color, 1, CustomRPC::RoleId::Bestfalsecharge);
IntroDate *IntroDate::ResearcherIntro = new IntroDate(L"Researcher", RoleClass::Researcher::color, 1, CustomRPC::RoleId::Researcher, TeamRoleType::Neutral);
IntroDate *IntroDate::SelfBomberIntro = new IntroDate(L"SelfBomber", RoleClass::SelfBomber::color, 1, CustomRPC::RoleId::SelfBomber, TeamRoleType::Impostor);
IntroDate *IntroDate::GodIntro = new IntroDate(L"God", RoleClass::God::color, 1, CustomRPC::RoleId::God, TeamRoleType::Neutral);
IntroDate *IntroDate::AllCleanerIntro = new IntroDate(L"AllCleaner", RoleClass::AllCleaner::color, 1, CustomRPC::RoleId::AllCleaner, TeamRoleType::Impostor);
IntroDate *IntroDate::NiceNekomataIntro = new IntroDate(L"NiceNekomata", RoleClass::NiceNekomata::color, 3, CustomRPC::RoleId::NiceNekomata);
IntroDate *IntroDate::EvilNekomataIntro = new IntroDate(L"EvilNekomata", RoleClass::EvilNekomata::color, 1, CustomRPC::RoleId::EvilNekomata, TeamRoleType::Impostor);
IntroDate *IntroDate::JackalFriendsIntro = new IntroDate(L"JackalFriends", RoleClass::JackalFriends::color, 2, CustomRPC::RoleId::JackalFriends);
IntroDate *IntroDate::DoctorIntro = new IntroDate(L"Doctor", RoleClass::Doctor::color, 1, CustomRPC::RoleId::Doctor);
IntroDate *IntroDate::CountChangerIntro = new IntroDate(L"CountChanger", RoleClass::CountChanger::color, 2, CustomRPC::RoleId::CountChanger, TeamRoleType::Impostor);
IntroDate *IntroDate::PursuerIntro = new IntroDate(L"Pursuer", RoleClass::Pursuer::color, 3, CustomRPC::RoleId::Pursuer, TeamRoleType::Impostor);
IntroDate *IntroDate::MinimalistIntro = new IntroDate(L"Minimalist", RoleClass::Minimalist::color, 2, CustomRPC::RoleId::Minimalist, TeamRoleType::Impostor);
IntroDate *IntroDate::HawkIntro = new IntroDate(L"Hawk", RoleClass::Hawk::color, 1, CustomRPC::RoleId::Hawk, TeamRoleType::Impostor);
IntroDate *IntroDate::EgoistIntro = new IntroDate(L"Egoist", RoleClass::Egoist::color, 1, CustomRPC::RoleId::Egoist, TeamRoleType::Neutral);
IntroDate *IntroDate::NiceRedRidingHoodIntro = new IntroDate(L"NiceRedRidingHood", RoleClass::NiceRedRidingHood::color, 1, CustomRPC::RoleId::NiceRedRidingHood);
IntroDate *IntroDate::EvilEraserIntro = new IntroDate(L"EvilEraser", RoleClass::EvilEraser::color, 1, CustomRPC::RoleId::EvilEraser, TeamRoleType::Impostor);
IntroDate *IntroDate::WorkpersonIntro = new IntroDate(L"Workperson", RoleClass::Workperson::color, 1, CustomRPC::RoleId::Workperson, TeamRoleType::Neutral);
IntroDate *IntroDate::MagazinerIntro = new IntroDate(L"Magaziner", RoleClass::Magaziner::color, 1, CustomRPC::RoleId::Magaziner, TeamRoleType::Impostor);
IntroDate *IntroDate::MayorIntro = new IntroDate(L"Mayor", RoleClass::Mayor::color, 1, CustomRPC::RoleId::Mayor);

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
