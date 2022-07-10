#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{
	class CustomColors
	{
	protected:
		static std::unordered_map<int, std::wstring> ColorStrings;
	public:
		static std::vector<int> lighterColors;
		static unsigned int pickableColors;

		/* version 1
		private static readonly List<int> ORDER = new() { 7, 17, 5, 33, 4,
		                                                            30, 0, 19, 27, 3,
		                                                            13, 25, 18, 15, 23,
		                                                            8, 32, 1, 21, 31,
		                                                            10, 34, 12, 14, 28,
		                                                            22, 29, 11, 26, 2,
		                                                            20, 24, 9, 16, 6 }; */
		static void Load();

	protected:
		class CustomColor
		{
		public:
			std::wstring longname;
			Color32 *color;
			Color32 *shadow;
			bool isLighterColor = false;
			virtual ~CustomColor()
			{
				delete color;
				delete shadow;
			}

		};

	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class CustomColorPatches
		class CustomColorPatches final
		{
		private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(TranslationController), nameof(TranslationController.GetString), new[] { typeof(StringNames), typeof(Il2CppReferenceArray<Il2CppSystem.Object>) })] private class ColorStringPatch
			class ColorStringPatch
			{
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ref string __result, [HarmonyArgument(0)] StringNames name)
				static bool Prefix(std::wstring &__result, StringNames *name);
			};
		private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerTab), nameof(PlayerTab.OnEnable))] private static class PlayerTabEnablePatch
			class PlayerTabEnablePatch final
			{
			public:
				static void Postfix(PlayerTab *__instance);
			};
		private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(SaveManager), nameof(SaveManager.LoadPlayerPrefs))] private static class LoadPlayerPrefsPatch
			class LoadPlayerPrefsPatch final
			{ // Fix Potential issues with broken colors
			private:
				static bool needsPatch;
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix([HarmonyArgument(0)] bool overrideLoad)
				static void Prefix(bool overrideLoad);
				static void Postfix();
			};
		private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.CheckColor))] private static class PlayerControlCheckColorPatch
			class PlayerControlCheckColorPatch final
			{
			private:
				static bool isTaken(PlayerControl *player, unsigned int color);
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] byte bodyColor)
				static bool Prefix(PlayerControl *__instance, unsigned char bodyColor);
			};
		};
	};
}
