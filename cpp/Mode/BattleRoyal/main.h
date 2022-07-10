#pragma once

#include "../../EndGame/EndGame.h"
#include "../SuperHostRoles/FixedUpdate.h"
#include "../SuperHostRoles/EndGameCheck.h"
#include <unordered_map>
#include <vector>
#include <optional>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
using namespace SuperNewRoles::EndGame;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::BattleRoyal
{
	class main
	{
	public:
		static void FixedUpdate();
		static int AlivePlayer;
		static int AllPlayer;
		static bool IsStart;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.CoExitVent))] class CoExitVentPatch
		class CoExitVentPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerPhysics __instance, [HarmonyArgument(0)] int id)
			static bool Prefix(PlayerPhysics *__instance, int id);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.CoEnterVent))] class CoEnterVentPatch
		class CoEnterVentPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerPhysics __instance, [HarmonyArgument(0)] int id)
			static bool Prefix(PlayerPhysics *__instance, int id);
		};
	public:
		static std::unordered_map<unsigned char, std::optional<int>> VentData;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.RepairSystem))] class RepairSystemPatch
		class RepairSystemPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
			static bool Prefix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
			static void Postfix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount);
		};
	public:
		static std::vector<PlayerControl*> Winners;
		static bool IsViewAlivePlayer;
		static bool EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static float StartSeconds;
		static bool IsCountOK;
	private:
		static float UpdateTime;
	public:
		static bool IsTeamBattle;
		static std::vector<std::vector<PlayerControl*>> Teams;
	private:
		static bool IsSeted;
	public:
		static void ClearAndReload();
	public:
		class ChangeRole final
		{
		public:
			static void Postfix();
		};
	};
}
