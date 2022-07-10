#pragma once

#include <string>
#include <vector>
#include <functional>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Harmony] public class CustomOverlays
	class CustomOverlays
	{
	public:
		static Sprite *helpButton;
	private:
		static Sprite *colorBG;
		static SpriteRenderer *meetingUnderlay;
		static SpriteRenderer *infoUnderlay;
		static TMPro::TextMeshPro *infoOverlayRules;
		static TMPro::TextMeshPro *infoOverlayRoles;
	public:
		static bool overlayShown;

		static void resetOverlays();

		static bool initializeOverlays();

		static void showBlackBG();

		static void hideBlackBG();

		static void showInfoOverlay();

		static void hideInfoOverlay();

		static void toggleInfoOverlay();

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(KeyboardJoystick), nameof(KeyboardJoystick.Update))] public static class CustomOverlayKeybinds
		class CustomOverlayKeybinds final
		{
		public:
			static void Postfix(KeyboardJoystick *__instance);
		};
	};
}
