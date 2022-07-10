#pragma once

#include "../Roles/EvilGambler.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.Roles.EvilGambler;

namespace SuperNewRoles::Buttons
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.OnGameEnd))] public class OnGameTimeEnd
	class OnGameTimeEnd
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(AmongUsClient __instance, [HarmonyArgument(0)] ref EndGameResult endGameResult)
		static void Prefix(AmongUsClient *__instance, EndGameResult *&endGameResult);
		static void Patch();
	};
}
