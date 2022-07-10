#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.Update))] class MeetingUpdatePatch
	class MeetingUpdatePatch
	{
	public:
		static void Postfix(MeetingHud *__instance);
		static PassiveButton *RightButton;
		static PassiveButton *LeftButton;
		static bool IsFlag;
		static bool IsSHRFlag;
	private:
		static Sprite *m_Meeting_AreaTabChange;
	public:
		static Sprite *getMeetingAreaTabChange();
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.UpdateButtons))] class meetingsheriff_updatepatch
	class meetingsheriff_updatepatch
	{
	private:
		static void Postfix(MeetingHud *__instance);
	public:
		static void Change(MeetingHud *__instance, bool right);
		static int index;
		static std::vector<PlayerVoteArea*> PlayerVoteAreas;
		static std::vector<Vector3*> Positions;
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.Start))] class MeetingSheriff_Patch
	class MeetingSheriff_Patch
	{
	public:
		static bool IsMeetingSheriffKill(PlayerControl *Target);
	private:
		static void MeetingSheriffOnClick(int Index, MeetingHud *__instance);
		static void Event(MeetingHud *__instance);

		static void Postfix(MeetingHud *__instance);
	public:
		static GameObject *Right;
		static GameObject *Left;
	private:
		static void CreateAreaButton(MeetingHud *__instance);
	public:
		static void right();
		static void left();
	};
}
