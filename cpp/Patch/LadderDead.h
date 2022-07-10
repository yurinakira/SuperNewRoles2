#pragma once

#include "FixedUpdate.h"
#include <unordered_map>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class LadderDead final
	{
	public:
		static void Reset();
		static void FixedUpdate();
		static std::unordered_map<unsigned char, Vector3*> TargetLadderData;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerPhysics), nameof(PlayerPhysics.ClimbLadder))] class ladder
		class ladder
		{
		public:
			static void Postfix(PlayerPhysics *__instance, Ladder *source, unsigned char climbLadderSid);
		};
	};
}
