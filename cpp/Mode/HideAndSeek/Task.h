#pragma once

#include <vector>

using namespace HarmonyLib;

namespace SuperNewRoles::Mode::HideAndSeek
{
	class Task
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.MurderPlayer))] public static class DeadPlayerTaskPatch
		class DeadPlayerTaskPatch final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
			static void Postfix(PlayerControl *__instance, PlayerControl *target);
		};
	public:
		static void TaskCountHideAndSeek(GameData *__instance);
	};
}
