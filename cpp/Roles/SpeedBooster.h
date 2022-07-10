#pragma once

#include "Speeder.h"
#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class SpeedBooster
	{
	public:
		static void ResetCoolDown();
		static void BoostStart();
		static void ResetSpeed();
		static void SpeedBoostEnd();
		static bool IsSpeedBooster(PlayerControl *Player);
		static void EndMeeting();
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.FixedUpdate))] public static class PlayerPhysicsSpeedPatch
		class PlayerPhysicsSpeedPatch final
		{
		public:
			static void Postfix(PlayerPhysics *__instance);
		};
	};
}
