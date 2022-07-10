#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class Fox
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.SetHudActive))] class SetHudActivePatch
		class SetHudActivePatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(HudManager __instance, [HarmonyArgument(0)] bool isActive)
			static void Postfix(HudManager *__instance, bool isActive);
		};
	};
}
