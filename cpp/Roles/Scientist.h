#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Scientist
	{
	public:
		static void EndMeeting();
		static void ResetCoolDown();
		static void Start();
		static void ResetScientist();
		static void ScientistEnd();
		static void setOpacity(PlayerControl *player, float opacity, bool cansee);
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.FixedUpdate))] public static class PlayerPhysicsScientist
		class PlayerPhysicsScientist final
		{
		public:
			static void Postfix(PlayerPhysics *__instance);
		};
	};
}
