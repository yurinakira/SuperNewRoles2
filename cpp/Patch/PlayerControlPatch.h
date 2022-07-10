#pragma once

#include "../Helpers/DesyncHelpers.h"
#include "../ModHelpers.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.Helpers.DesyncHelpers;
using namespace SuperNewRoles;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.ModHelpers;

namespace SuperNewRoles::Patches
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.Shapeshift))] class RpcShapesihftPatch
	class RpcShapesihftPatch
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target, [HarmonyArgument(1)] bool shouldAnimate)
		static bool Prefix(PlayerControl *__instance, PlayerControl *target, bool shouldAnimate);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.CheckProtect))] class CheckProtectPatch
	class CheckProtectPatch
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
		static bool Prefix(PlayerControl *__instance, PlayerControl *target);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShapeshifterMinigame), nameof(ShapeshifterMinigame.Shapeshift))] class ShapeshifterMinigameShapeshiftPatch
	class ShapeshifterMinigameShapeshiftPatch
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ShapeshifterMinigame __instance, [HarmonyArgument(0)] PlayerControl player)
		static bool Prefix(ShapeshifterMinigame *__instance, PlayerControl *player);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(KillButton), nameof(KillButton.DoClick))] class KillButtonDoClickPatch
	class KillButtonDoClickPatch
	{
	public:
		static bool Prefix(KillButton *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.CheckMurder))] static class CheckMurderPatch
	class CheckMurderPatch final
	{
	public:
		static bool isKill;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
		static bool Prefix(PlayerControl *__instance, PlayerControl *target);
		static void RpcCheckExile(PlayerControl *__instance);
		static void RpcMurderPlayerCheck(PlayerControl *__instance, PlayerControl *target);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.SetKillTimer))] static class PlayerControlSetCoolDownPatch
	class PlayerControlSetCoolDownPatch final
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] float time)
		static bool Prefix(PlayerControl *__instance, float time);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.MurderPlayer))] public static class MurderPlayerPatch
	class MurderPlayerPatch final
	{
	public:
		static bool resetToCrewmate;
		static bool resetToDead;
		static bool Prefix(PlayerControl *__instance, PlayerControl *target);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
		static void Postfix(PlayerControl *__instance, PlayerControl *target);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.Exiled))] public static class ExilePlayerPatch
	class ExilePlayerPatch final
	{
	public:
		static void Postfix(PlayerControl *__instance);
	};
	class PlayerControlFixedUpdatePatch final
	{
	public:
		static PlayerControl *setTarget(bool onlyCrewmates = false, bool targetPlayersInVents = false, std::vector<PlayerControl*> &untargetablePlayers = std::vector<PlayerControl>(), PlayerControl *targetingPlayer = nullptr);
	};
}
