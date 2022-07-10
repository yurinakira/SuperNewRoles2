#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(GameStartManager.Start))] public class inversion
	class inversion
	{
	public:
		static GameObject *skeld;
		static GameObject *mira;
		static GameObject *polus;
		static GameObject *airship;
		static void Prefix();
	};
}
