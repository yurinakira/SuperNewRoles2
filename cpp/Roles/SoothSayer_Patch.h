#pragma once

#include <string>
#include <algorithm>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.UpdateButtons))] class SoothSayer_updatepatch
	class SoothSayer_updatepatch
	{
	private:
		static void Postfix(MeetingHud *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MeetingHud), nameof(MeetingHud.Start))] class SoothSayer_Patch
	class SoothSayer_Patch
	{
	private:
		static std::wstring namedate;
		static void SoothSayerOnClick(int Index, MeetingHud *__instance);
		static void Event(MeetingHud *__instance);

		static void SpiritOnClick(int Index, MeetingHud *__instance);
		static void spiritEvent(MeetingHud *__instance);

		static void Postfix(MeetingHud *__instance);
	};
}
