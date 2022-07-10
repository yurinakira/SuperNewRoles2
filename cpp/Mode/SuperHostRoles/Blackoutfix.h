#pragma once

#include <vector>

using namespace HarmonyLib;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class Blackoutfix
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.CheckForEndVoting))] public class CheckForEndVotingPatch
		class CheckForEndVotingPatch
		{
		public:
			static void Prefix(MeetingHud *__instance);
		};
	public:
		static void EndMeetingPatch();
	};
}
