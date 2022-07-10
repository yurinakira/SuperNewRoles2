#pragma once

//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "../Mode/SuperHostRoles/ShipStatus.h"
#include "../Intro/IntroDate.h"
#include "../Mode/SuperHostRoles/Intro.h"
#include "FinalStatus.h"
#include "CustomEndReason.h"
#include "../Mode/SuperHostRoles/WrapUp.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>
#include <stdexcept>
#include <optional>
#include "../stringhelper.h"
#include "../stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace SuperNewRoles::EndGame { class PlayerRoleInfo; }
namespace SuperNewRoles::EndGame { class PlayerStatistics; }

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::EndGame
{
	enum class WinCondition
	{
		Default,
		HAISON,
		JesterWin,
		JackalWin,
		QuarreledWin,
		GodWin,
		EgoistWin,
		WorkpersonWin,
		LoversWin,
		MadJesterWin,
		FalseChargesWin,
		FoxWin,
		DemonWin,
		ArsonistWin,
		VultureWin,
		TunaWin,
		NeetWin,
		BugEnd
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus))] public class ShipStatusPatch
	class ShipStatusPatch
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix][HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.IsGameOverDueToDeath))] public static void Postfix2(ShipStatus __instance, ref bool __result)
		static void Postfix2(ShipStatus *__instance, bool &__result);
	};
	class AdditionalTempData final
	{
		// Should be implemented using a proper GameOverReason in the future
	public:
		static std::vector<PlayerRoleInfo*> playerRoles;
		static GameOverReason *gameOverReason;
		static WinCondition winCondition;
		static std::vector<WinCondition> additionalWinConditions;

		static std::unordered_map<int, PlayerControl*> plagueDoctorInfected;
		static std::unordered_map<int, float> plagueDoctorProgress;

		static void clear();
	public:
		class PlayerRoleInfo
		{
		private:
			std::wstring PlayerName;
			std::wstring NameSuffix;
			std::vector<Intro::IntroDate*> Roles;
			std::wstring RoleString;
			int TasksCompleted = 0;
			int TasksTotal = 0;
			int PlayerId = 0;
			int ColorId = 0;
			FinalStatus Status = static_cast<FinalStatus>(0);
			Intro::IntroDate *IntroDate;
			Intro::IntroDate *GhostIntroDate;

		public:
			std::wstring getPlayerName() const;
			void setPlayerName(const std::wstring &value);
			std::wstring getNameSuffix() const;
			void setNameSuffix(const std::wstring &value);
			std::vector<Intro::IntroDate*> getRoles() const;
			void setRoles(const std::vector<Intro::IntroDate*> &value);
			std::wstring getRoleString() const;
			void setRoleString(const std::wstring &value);
			int getTasksCompleted() const;
			void setTasksCompleted(int value);
			int getTasksTotal() const;
			void setTasksTotal(int value);
			int getPlayerId() const;
			void setPlayerId(int value);
			int getColorId() const;
			void setColorId(int value);
			FinalStatus getStatus() const;
			void setStatus(FinalStatus value);
			Intro::IntroDate *getIntroDate() const;
			void setIntroDate(Intro::IntroDate *value);
			Intro::IntroDate *getGhostIntroDate() const;
			void setGhostIntroDate(Intro::IntroDate *value);
		};
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(EndGameManager), nameof(EndGameManager.SetEverythingUp))] public class EndGameManagerSetUpPatch
	class EndGameManagerSetUpPatch
	{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
