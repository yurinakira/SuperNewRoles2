#pragma once

#include <string>
#include <vector>
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnhollowerBaseLib;

namespace SuperNewRoles::Roles
{
	class Assassin final
	{
		//元:https://github.com/yukieiji/ExtremeRoles/blob/master/ExtremeRoles/Patches/AirShipStatusPatch.cs
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AirshipStatus), nameof(AirshipStatus.PrespawnStep))] public static class AirshipStatusPrespawnStepPatch
		class AirshipStatusPrespawnStepPatch final
		{
		public:
			static bool Prefix();
		};
	public:
		static void AddChat(PlayerControl *sourcePlayer, const std::wstring &chatText);
		static void WrapUp(GameData::PlayerInfo *exiled);
	};
}
