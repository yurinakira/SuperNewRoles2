#pragma once

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.StartGame))] public class StartGame
	class StartGame
	{
	public:
		static void Postfix(PlayerControl *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AbilityButton), nameof(AbilityButton.Update))] public class AbilityUpdate
	class AbilityUpdate
	{
	public:
		static void Postfix(AbilityButton *__instance);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ControllerManager), nameof(ControllerManager.Update))] class DebugManager
	class DebugManager
	{
	public:
		static void Postfix(ControllerManager *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.FixedUpdate))] public class FixedUpdate
	class FixedUpdate
	{
	private:
		static void setBasePlayerOutlines();

		static bool ProDown;
	public:
		static bool IsProDown;

		static void Postfix(PlayerControl *__instance);
	};
}
