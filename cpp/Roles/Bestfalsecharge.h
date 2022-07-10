#pragma once

using namespace HarmonyLib;
using namespace Hazel;

namespace SuperNewRoles::Roles
{
	class Bestfalsecharge
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.VotingComplete))] public class MeetingEnd
		class MeetingEnd
		{
		private:
			static void Prefix(MeetingHud *__instance);
		};
	};
}
