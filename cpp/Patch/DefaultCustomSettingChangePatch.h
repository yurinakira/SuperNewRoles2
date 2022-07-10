#pragma once

#include <string>
#include <vector>

using namespace BepInEx::Configuration;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class DefaultCustomSettingChangePatch
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameSettingMenu), nameof(GameSettingMenu.Start))] class GameSettingMenuStartPatch
		class GameSettingMenuStartPatch
		{
		public:
			static void Prefix(GameSettingMenu *__instance);

			static void Postfix(GameSettingMenu *__instance);
		};
	};
}
