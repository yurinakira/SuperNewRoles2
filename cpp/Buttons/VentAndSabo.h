#pragma once

#include <limits>

using namespace HarmonyLib;
using namespace SuperNewRoles::MapOptions;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Buttons
{
	class VentAndSabo final
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MapBehaviour), nameof(MapBehaviour.ShowNormalMap))] class MapBehaviourPatch
		class MapBehaviourPatch
		{
		public:
			static bool Prefix(MapBehaviour *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Vent), nameof(Vent.EnterVent))] class EnterVentAnimPatch
		class EnterVentAnimPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, [HarmonyArgument(0)] PlayerControl pc)
			static bool Prefix(Vent *__instance, PlayerControl *pc);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Vent), nameof(Vent.ExitVent))] class ExitVentAnimPatch
		class ExitVentAnimPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, [HarmonyArgument(0)] PlayerControl pc)
			static bool Prefix(Vent *__instance, PlayerControl *pc);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Vent), nameof(Vent.CanUse))] public static class VentCanUsePatch
		class VentCanUsePatch final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(Vent __instance, ref float __result, [HarmonyArgument(0)] GameData.PlayerInfo pc, [HarmonyArgument(1)] out bool canUse, [HarmonyArgument(2)] out bool couldUse)
			static bool Prefix(Vent *__instance, float &__result, GameData::PlayerInfo *pc, bool &canUse, bool &couldUse);
		};
	public:
		class VentButtonVisibilityPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Vent), nameof(Vent.Use))] public static class VentUsePatch
		class VentUsePatch final
		{
		public:
			static bool Prefix(Vent *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(SabotageButton), nameof(SabotageButton.DoClick))] public static class SabotageButtonDoClickPatch
		class SabotageButtonDoClickPatch final
		{
		public:
			static bool Prefix(SabotageButton *__instance);
		};
	};
}
