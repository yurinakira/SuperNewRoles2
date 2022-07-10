#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Map
{
	class SetPosition
	{
		/*
		[HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Begin))]
		public static class ShipStatusBeginPatch
		{
		    [HarmonyPostfix]
		    [HarmonyPatch]
		    public static void Postfix(ShipStatus __instance)
		    {
		        ApplyChanges(__instance);
		    }
		}
		*/
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Awake))] public static class ShipStatusAwakePatch
		class ShipStatusAwakePatch final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix][HarmonyPatch] public static void Postfix(ShipStatus __instance)
			static void Postfix(ShipStatus *__instance);
		};
	public:
		static void ApplyChanges(ShipStatus *__instance);
	};
}
