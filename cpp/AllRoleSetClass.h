#pragma once

#include "CustomRPC/CustomRPCSender.h"
#include "CustomRPC/CustomRPC.h"
#include <string>
#include <vector>
#include <stdexcept>
#include "stringhelper.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles
{

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetRole))] class RpcSetRoleReplacer
	class RpcSetRoleReplacer
	{
	public:
		static bool doReplace;
		static CustomRpcSender *sender;
		static std::vector<(PlayerControl, RoleTypes)*> StoragedData;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] RoleTypes roleType)
		static bool Prefix(PlayerControl *__instance, RoleTypes *roleType);
		static void Release();
		static void StartReplace(CustomRpcSender *sender);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.StartGame))] class startgamepatch
	class startgamepatch
	{
	public:
		static void Postfix();
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(RoleManager), nameof(RoleManager.SelectRoles))] class RoleManagerSelectRolesPatch
	class RoleManagerSelectRolesPatch
	{
	public:
		static bool IsNotPrefix;
		static bool IsRPCSetRoleOK;
		static bool IsSetRoleRpc;
		static bool IsShapeSet;
		static bool IsNotDesync;
		static bool Prefix();
		static void Postfix();
	};
	class AllRoleSetClass
	{
	public:
		static std::vector<PlayerControl*> impostors;
		static std::vector<RoleId> Impoonepar;
		static std::vector<RoleId> Imponotonepar;
		static std::vector<RoleId> Neutonepar;
		static std::vector<RoleId> Neutnotonepar;
		static std::vector<RoleId> Crewonepar;
		static std::vector<RoleId> Crewnotonepar;
		static std::vector<PlayerControl*> CrewMatePlayers;
		static std::vector<PlayerControl*> ImpostorPlayers;

		static bool Assigned;

		static int ImpostorPlayerNum;
		static int ImpostorGhostRolePlayerNum;
		static int NeutralPlayerNum;
		static int NeutralGhostRolePlayerNum;
		static int CrewMatePlayerNum;
		static int CrewMateGhostRolePlayerNum;

		static void AllRoleSet();
		static void QuarreledRandomSelect();

		static void LoversRandomSelect();
		static void SetPlayerNum();
		static void ImpostorRandomSelect();
		static void NeutralRandomSelect();
		static void CrewMateRandomSelect();
		static float GetPlayerCount(RoleId RoleDate);
		static void CrewOrImpostorSet();
		static void OneOrNotListSet();
	};
}
