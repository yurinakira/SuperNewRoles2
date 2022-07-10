#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Patch
{

	//Town Of Plusより!
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] public static class Zoom
	class Zoom final
	{
	public:
		static void Postfix(HudManager *__instance);
	};
}
