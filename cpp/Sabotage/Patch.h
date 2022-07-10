#pragma once

#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Sabotage
{
	class Patch
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.OpenMeetingRoom))] class OpenMeetingPatch
		class OpenMeetingPatch
		{
		public:
			static void Prefix(HudManager *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(InfectedOverlay), nameof(InfectedOverlay.Update))] class SetUpCustomButton
		class SetUpCustomButton
		{
		public:
			static void Postfix(InfectedOverlay *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(InfectedOverlay), nameof(InfectedOverlay.Start))] class SetUpCustomSabotageButton
		class SetUpCustomSabotageButton
		{
		public:
			static void Postfix(InfectedOverlay *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(EmergencyMinigame), nameof(EmergencyMinigame.Update))] class EmergencyUpdatePatch
		class EmergencyUpdatePatch
		{
		public:
			static void Postfix(EmergencyMinigame *__instance);
		};
	};
}
