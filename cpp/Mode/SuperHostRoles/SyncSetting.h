#pragma once

#include <vector>
#include <algorithm>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class SyncSetting final
	{
	public:
		static GameOptionsData *OptionData;
		static void CustomSyncSettings(PlayerControl *player);
		static float KillCoolSet(float cool);
		static void MurderSyncSetting(PlayerControl *player);
		static void GamblersetCool(PlayerControl *p);
		static void CustomSyncSettings();
		static GameOptionsData *DeepCopy(GameOptionsData *opt);
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.StartGame))] public class StartGame
		class StartGame
		{
		public:
			static void Prefix();
			static void Postfix();
		};
	};
}
