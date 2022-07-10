#pragma once

#include "../EndGame/EndGame.h"
#include "../CustomOption/CustomOptionModel.h"
#include "../Patch/FixedUpdate.h"
#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.CloseDoorsOfType))] class CloseDoorsPatch
	class CloseDoorsPatch
	{
	public:
		static bool Prefix(ShipStatus *__instance);
	};
	enum class ModeId
	{
		No,
		Default,
		HideAndSeek,
		BattleRoyal,
		SuperHostRoles,
		Zombie,
		RandomColor,
		NotImpostorCheck,
		Detective,
		Werewolf,
		CopsRobbers,
		LevelUp
	};
	class ModeHandler
	{
	public:
		static ModeId thisMode;
		static void ClearAndReload();
		static std::vector<std::wstring> modes; //ModTranslation.getString("WerewolfModeName") };

		static const std::wstring PlayingOnSuperNewRoles;

		static CustomOptionBlank *Mode;
		static CustomOption::CustomOption *ModeSetting;
		static CustomOption::CustomOption *ThisModeSetting;
		static Il2CppSystem::Collections::Generic::List<PlayerControl*> *TeamHandler(IntroCutscene *__instance);
		static void IntroHandler(IntroCutscene *__instance);
		static void YouAreIntroHandler(IntroCutscene *__instance);
		static void OptionLoad();
		static void HudUpdate(HudManager *__instance);
		static void FixedUpdate(PlayerControl *__instance);
		static void Wrapup(GameData::PlayerInfo *exiled);
		static ModeId GetMode(bool IsChache = true);
		static std::wstring GetThisModeIntro();
		static bool isMode(std::vector<ModeId> &modes);
		static bool isMode(ModeId mode, bool IsChache = true);
		static bool EndGameChecks(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static bool IsBlockVanilaRole();
		static bool IsBlockGuardianAngelRole();
	};
}
