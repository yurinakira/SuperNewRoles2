#pragma once

#include <any>

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;
using namespace UnityEngine::AddressableAssets;
using namespace UnityEngine::ResourceManagement::AsyncOperations;

namespace SuperNewRoles::MapCustoms
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Awake))] public class AddVitals
	class AddVitals
	{
	public:
		static void Postfix();
		static GameObject *getPolusObject();
		static ShipStatus *Polus;
		static System::Collections::IEnumerator *LoadPolus();
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.Awake))] public static class AmongUsClient_Awake_Patch
	class AmongUsClient_Awake_Patch final
	{
	private:
		static bool Loaded;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPrefix][HarmonyPriority(900)] public static void Prefix(AmongUsClient __instance)
		static void Prefix(AmongUsClient *__instance);
	};
}
