#pragma once

#include <unordered_map>
#include <any>

using namespace HarmonyLib;
using namespace Il2CppSystem;

namespace SuperNewRoles
{
	class MapUtilities final
	{
	public:
		static ShipStatus *CachedShipStatus;

		static void MapDestroyed();

	private:
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: private static readonly Dictionary<SystemTypes, Object> _systems = new();
		static std::unordered_map<SystemTypes*, std::any> _systems;
	public:
		static std::unordered_map<SystemTypes*, std::any> getSystems();

	private:
		static void GetSystems();
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Awake))] public static class ShipStatus_Awake_Patch
	class ShipStatus_Awake_Patch final
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix, HarmonyPriority(Priority.Last)] public static void Postfix(ShipStatus __instance)
		static void Postfix(ShipStatus *__instance);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.OnDestroy))] public static class ShipStatus_OnDestroy_Patch
	class ShipStatus_OnDestroy_Patch final
	{
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix, HarmonyPriority(Priority.Last)] public static void Postfix()
		static void Postfix();
	};
}
