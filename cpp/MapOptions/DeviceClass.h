#pragma once

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::MapOptions
{
	class DeviceClass
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MapConsole), nameof(MapConsole.Use))] public static class MapConsoleUsePatch
		class MapConsoleUsePatch final
		{
		public:
			static bool Prefix(MapConsole *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MapCountOverlay), nameof(MapCountOverlay.Update))] class MapCountOverlayUpdatePatch
		class MapCountOverlayUpdatePatch
		{
		public:
			static bool Prefix(MapConsole *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(VitalsMinigame), nameof(VitalsMinigame.Update))] class VitalsDevice
		class VitalsDevice
		{
		private:
			static void Postfix(VitalsMinigame *__instance);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(SurveillanceMinigame), nameof(SurveillanceMinigame.Update))] class SurveillanceMinigameUpdatePatch
		class SurveillanceMinigameUpdatePatch
		{
		public:
			static void Postfix(SurveillanceMinigame *__instance);
		};

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlanetSurveillanceMinigame), nameof(PlanetSurveillanceMinigame.Update))] class PlanetSurveillanceMinigameUpdatePatch
		class PlanetSurveillanceMinigameUpdatePatch
		{
		public:
			static void Postfix(PlanetSurveillanceMinigame *__instance);
		};

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(SecurityLogGame), nameof(SecurityLogGame.Update))] class SecurityLogGameUpdatePatch
		class SecurityLogGameUpdatePatch
		{
		public:
			static void Postfix(SecurityLogGame *__instance);
		};
	};
}
