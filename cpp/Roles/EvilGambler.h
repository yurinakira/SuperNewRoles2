#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Roles
{
	class EvilGambler
	{
	public:
		class EvilGamblerMurder final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
			static void Prefix(PlayerControl *__instance, PlayerControl *target);
		};
	};
}
