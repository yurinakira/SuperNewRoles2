#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class Lovers
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameData), nameof(GameData.HandleDisconnect), new Type[] { typeof(PlayerControl), typeof(DisconnectReasons) })] class HandleDisconnectPatch
		class HandleDisconnectPatch
		{
		public:
			static void Postfix(GameData *__instance, PlayerControl *player, DisconnectReasons *reason);
		};
	};
}
