#pragma once

#define _USE_MATH_DEFINES
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Kunoichi final
	{
	public:
		static PlayerControl *GetShootPlayer(float shotSize = 0.75f);
		static void KillButtonClick();
		static void Update();

		static void setOpacity(PlayerControl *player, float opacity, bool cansee);
		static void WrapUp();
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
