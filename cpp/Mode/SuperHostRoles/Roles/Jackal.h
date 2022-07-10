#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class Jackal
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.StartGame))] class SpawnBot
		class SpawnBot
		{
		public:
			static void Prefix(AmongUsClient *__instance);
		};
	};
}
