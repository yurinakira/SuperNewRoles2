#pragma once

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class WallHack
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] class HudManagerPatch
		class HudManagerPatch
		{
		public:
			static void Postfix(HudManager *__instance);
		};
	};
}
