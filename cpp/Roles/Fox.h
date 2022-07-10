#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Fox
	{
	public:
		static void setPlayerOutline(PlayerControl *target, Color *color);

	public:
		class FoxMurderPatch final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
			static void Prefix(PlayerControl *__instance, PlayerControl *target);
		};
	};
}
