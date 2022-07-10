#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class MorePatch
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.CompleteTask))] class PlayerControlCompleteTaskPatch
		class PlayerControlCompleteTaskPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};

	public:
		static bool RepairSystem(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount);
		static void StartMeeting(MeetingHud *__instance);
		static void MeetingEnd();
	};
}
