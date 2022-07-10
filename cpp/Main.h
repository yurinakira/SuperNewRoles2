#pragma once

#include "Debugger.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "tangible_filesystem.h"

using namespace BepInEx;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [BepInPlugin(Id, "SuperNewRoles", VersionString)][BepInDependency(SubmergedCompatibility.SUBMERGED_GUID, BepInDependency.DependencyFlags.SoftDependency)][BepInProcess("Among Us.exe")] public class SuperNewRolesPlugin : BasePlugin
	class SuperNewRolesPlugin : public BasePlugin
	{
	private:
		Harmony *Harmony = new Harmony(Id);

	public:
		static const std::wstring Id;

		//バージョンと同時にIsBetaも変える
		static const std::wstring VersionString;
		static bool isBeta();

		static System::Version *Version;
		static BepInEx::Logging::ManualLogSource *Logger;
		static Sprite *ModStamp;
		static int optionsPage;
		Harmony *getHarmony() const;
		static SuperNewRolesPlugin *Instance;
		static std::unordered_map<std::wstring, std::unordered_map<int, std::wstring>> StringDATE;
		static bool IsUpdate;
		static std::wstring NewVersion;
		static std::wstring thisname;

		void Load() override;
		/*
		[HarmonyPatch(typeof(TranslationController), nameof(TranslationController.GetString), new Type[] { typeof(StringNames), typeof(Il2CppReferenceArray<Il2CppSystem.Object>) })]
		class TranslateControllerMessagePatch
		{
		    static void Postfix(ref string __result, [HarmonyArgument(0)] StringNames id)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo(id+":"+__result);
		    }
		}*/
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(StatsManager), nameof(StatsManager.AmBanned), MethodType.Getter)] public static class AmBannedPatch
		class AmBannedPatch final
		{
		public:
			static void Postfix(bool &__result);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ChatController), nameof(ChatController.Update))] public static class ChatControllerAwakePatch
		class ChatControllerAwakePatch final
		{
		public:
			static void Prefix();
			static void Postfix(ChatController *__instance);
		};
	};
}
