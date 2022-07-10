#pragma once

#include <vector>
#include <functional>

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnityEngine;
using namespace UnityEngine::Events;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(RegionMenu), nameof(RegionMenu.Open))] public static class RegionMenuOpenPatch
	class RegionMenuOpenPatch final
	{
	private:
		static TextBoxTMP *ipField;
		static TextBoxTMP *portField;

	public:
		static void Postfix(RegionMenu *__instance);
		static std::vector<IRegionInfo*> defaultRegions;
		static void UpdateRegions();
	};
}
