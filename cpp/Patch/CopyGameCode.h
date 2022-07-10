#pragma once

#include <string>

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class CopyGameCode
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Start))] public class GameStartManagerStartPatch
		class GameStartManagerStartPatch
		{
		public:
			static void Postfix(GameStartManager *__instance);
		};
	};
}
