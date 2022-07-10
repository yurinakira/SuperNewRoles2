#pragma once

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Map
{
	class Patch final
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MapBehaviour), nameof(MapBehaviour.Awake))] class ChangeMapPatch
		class ChangeMapPatch
		{
		public:
			static void Postfix(MapBehaviour *__instance);
		};
	};
}
