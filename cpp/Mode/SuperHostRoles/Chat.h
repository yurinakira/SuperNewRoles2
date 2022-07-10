#pragma once

#include "../../EndGame/CustomEndReason.h"
#include <string>
#include <vector>
#include <optional>
#include "../../stringhelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::EndGame;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class Chat
	{
	public:
		static bool IsOldSHR;
		static std::optional<CustomGameOverReason> WinCond;
		static std::vector<PlayerControl*> Winner;
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Start))] public class GameStartManagerStartPatch
		class GameStartManagerStartPatch
		{
		public:
			static void Postfix();
		};
	};
}
