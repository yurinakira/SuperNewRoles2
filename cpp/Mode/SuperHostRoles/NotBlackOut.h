#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class NotBlackOut final
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.CheckForEndVoting))] class CheckForEndVotingPatch
		class CheckForEndVotingPatch
		{
		public:
			static void Prefix(MeetingHud *__instance);
		};
	public:
		static void EndMeetingPatch();
		static bool IsAntiBlackOut(PlayerControl *player);
		static void ResetPlayerCam(PlayerControl *pc, float delay = 0.0f);
	};
}
