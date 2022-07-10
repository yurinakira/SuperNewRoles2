#pragma once

#include "TitleMenuPatch.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace static UnityEngine::UI::Button;
//C# TO C++ CONVERTER TODO TASK: C# to C++ Converter could not confirm whether this is a namespace alias or a type alias:
//using Object = UnityEngine::Object;

namespace SuperNewRoles::Patches
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MainMenuManager), nameof(MainMenuManager.Start))] public class MainMenuPatch
	class MainMenuPatch
	{
	private:
		static bool horseButtonState;
		static Sprite *horseModeOffSprite;
		static Sprite *horseModeOnSprite;

		static void Prefix(MainMenuManager *__instance);
	};

	class HorseModeOption final
	{
	public:
		static bool enableHorseMode;

		static void clearAndReloadMapOptions();
	};
}
