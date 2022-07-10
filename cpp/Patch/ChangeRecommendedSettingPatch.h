#pragma once

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles

{
//TOHより!
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameOptionsData), nameof(GameOptionsData.SetRecommendations))] public static class ChangeRecommendedSettingPatch
	class ChangeRecommendedSettingPatch final
	{
	public:
		static bool Prefix(GameOptionsData *__instance, int numPlayers, GameModes *modes);
	};
}
