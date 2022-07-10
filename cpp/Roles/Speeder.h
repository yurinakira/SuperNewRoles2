#pragma once

#include "../Buttons/CustomButton.h"
#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Speeder
	{
	public:
		static void ResetCoolDown();
		static void DownStart();
		static void ResetSpeed();
		static void SpeedDownEnd();
		static bool IsSpeeder(PlayerControl *Player);
		static void EndMeeting();
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.FixedUpdate))] public static class PlayerPhysicsSpeedPatch
	class PlayerPhysicsSpeedPatch final
	{
	public:
		static void Postfix(PlayerPhysics *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] public static class HudManagerUpdatePatch
	class HudManagerUpdatePatch final
	{
	public:
		static void Postfix();
	};
}
