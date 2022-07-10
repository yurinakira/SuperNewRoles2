#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.CalculateLightRadius))] class LightPatch
	class LightPatch
	{
	public:
		static float GetNeutralLightRadius(ShipStatus *shipStatus, bool isImpostor);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ref float __result, ShipStatus __instance, [HarmonyArgument(0)] GameData.PlayerInfo player)
		static bool Prefix(float &__result, ShipStatus *__instance, GameData::PlayerInfo *player);
	};
}
