#pragma once

#include <vector>
#include <functional>

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace static PlayerControl;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{
	class MapCustomHandler
	{
	public:
		static bool isMapCustom(MapCustomId mapCustomId, bool IsChache = true);
	public:
		enum class MapCustomId
		{
			Skeld,
			Mira,
			Polus,
			Airship
		};
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(IntroCutscene), nameof(IntroCutscene.OnDestroy))] class IntroCutsceneOnDestroyPatch
	class IntroCutsceneOnDestroyPatch
	{
	public:
		static void Prefix(IntroCutscene *__instance);
	};
	class Extensions final
	{
	public:
		template<typename T>
		static void ForEach(std::vector<T> &self, std::function<void(T)> todo)
		{
			for (int i = 0; i < self.size(); i++)
			{
				todo(self[i]);
			}
		}
	};
}
