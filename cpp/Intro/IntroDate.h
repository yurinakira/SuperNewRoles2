#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "../CustomRPC/CustomRPC.h"
#include "../Roles/TeamRoleType.h"
#include "../CustomOption/CustomOptionModel.h"
#include <string>
#include <unordered_map>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Intro
{
	class IntroDate
	{
	public:
		static std::vector<IntroDate*> IntroDatas;
		static std::unordered_map<RoleId, IntroDate*> IntroDatasCache;
		static std::vector<IntroDate*> GhostRoleDatas;
		std::wstring NameKey;
		std::wstring Name;
		short TitleNum = 0;
		std::wstring TitleDesc;
		Color *color;
		CustomRPC::RoleId RoleId = static_cast<CustomRPC::RoleId>(0);
		std::wstring Description;
		TeamRoleType Team = static_cast<TeamRoleType>(0);
		bool IsGhostRole = false;
		virtual ~IntroDate()
		{
			delete color;
		}

	private:
		IntroDate(const std::wstring &NameKey, Color *color, short TitleNum, CustomRPC::RoleId RoleId, TeamRoleType team = TeamRoleType::Crewmate, bool IsGhostRole = false);
	public:
		static IntroDate *GetIntroDate(RoleId RoleId, PlayerControl *p = nullptr);
		static CustomRoleOption *GetOption(RoleId roleId);
		static std::wstring GetTitle(const std::wstring &name, short num);

		static IntroDate *CrewmateIntro;
		static IntroDate *ImpostorIntro;
		static IntroDate *SoothSayerIntro;
		static IntroDate *JesterIntro;
		static IntroDate *LighterIntro;
		static IntroDate *EvilLighterIntro;
		static IntroDate *EvilScientist;
		static IntroDate *SheriffIntro;
		static IntroDate *MeetingSheriffIntro;
		static IntroDate *JackalIntro;
		static IntroDate *SidekickIntro;
		static IntroDate *TeleporterIntro;
		static IntroDate *SpiritMediumIntro;
		static IntroDate *SpeedBoosterIntro;
		static IntroDate *EvilSpeedBoosterIntro;
		static IntroDate *TaskerIntro;
		static IntroDate *DoorrIntro;
		static IntroDate *EvilDoorrIntro;
		static IntroDate *ShielderIntro;
		static IntroDate *FreezerIntro;
		static IntroDate *SpeederIntro;
		static IntroDate *GuesserIntro;
		static IntroDate *EvilGuesserIntro;
		static IntroDate *VultureIntro;
		static IntroDate *NiceScientistIntro;
		static IntroDate *ClergymanIntro;
		static IntroDate *MadMateIntro;
		static IntroDate *BaitIntro;
		static IntroDate *HomeSecurityGuardIntro;
		static IntroDate *StuntManIntro;
		static IntroDate *MovingIntro;
		static IntroDate *OpportunistIntro;
		static IntroDate *NiceGamblerIntro;
		static IntroDate *EvilGamblerIntro;
		static IntroDate *BestfalsechargeIntro;
		static IntroDate *ResearcherIntro;
		static IntroDate *SelfBomberIntro;
		static IntroDate *GodIntro;
		static IntroDate *AllCleanerIntro;
		static IntroDate *NiceNekomataIntro;
		static IntroDate *EvilNekomataIntro;
		static IntroDate *JackalFriendsIntro;
		static IntroDate *DoctorIntro;
		static IntroDate *CountChangerIntro;
		static IntroDate *PursuerIntro;
		static IntroDate *MinimalistIntro;
		static IntroDate *HawkIntro;
		static IntroDate *EgoistIntro;
		static IntroDate *NiceRedRidingHoodIntro;
		static IntroDate *EvilEraserIntro;
		static IntroDate *WorkpersonIntro;
		static IntroDate *MagazinerIntro;
		static IntroDate *MayorIntro;
		static IntroDate *trueloverIntro;
		static IntroDate *TechnicianIntro;
		static IntroDate *SerialKillerIntro;
		static IntroDate *OverKillerIntro;
		static IntroDate *LevelingerIntro;
		static IntroDate *EvilMovingIntro;
		static IntroDate *AmnesiacIntro;
		static IntroDate *SideKillerIntro;
		static IntroDate *MadKillerIntro;
		static IntroDate *SurvivorIntro;
		static IntroDate *MadMayorIntro;
		static IntroDate *NiceHawkIntro;
		static IntroDate *BakeryIntro;
		static IntroDate *MadStuntManIntro;
		static IntroDate *MadHawkIntro;
		static IntroDate *MadJesterIntro;
		static IntroDate *FalseChargesIntro;
		static IntroDate *NiceTeleporterIntro;
		static IntroDate *CelebrityIntro;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
