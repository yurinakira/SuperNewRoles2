#pragma once

#include <unordered_map>
#include <vector>
#include <cstdint>

using namespace HarmonyLib;
using namespace InnerNet;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class CachedPlayer
	{
	public:
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: public static readonly Dictionary<IntPtr, CachedPlayer> PlayerPtrs = new();
		static std::unordered_map<std::intptr_t, CachedPlayer*> PlayerPtrs;
//C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection which allows modification of internal state:
//ORIGINAL LINE: public static readonly List<CachedPlayer> AllPlayers = new();
		static std::vector<CachedPlayer*> AllPlayers;
		static CachedPlayer *LocalPlayer;

		Transform *transform;
		PlayerControl *PlayerControl;
		PlayerPhysics *PlayerPhysics;
		CustomNetworkTransform *NetTransform;
		GameData::PlayerInfo *Data;
		unsigned char PlayerId = 0;
		unsigned int NetId = 0;

		virtual ~CachedPlayer()
		{
			delete transform;
			delete PlayerControl;
			delete PlayerPhysics;
			delete NetTransform;
			delete Data;
		}

		operator bool();

		operator PlayerControl*();
		operator PlayerPhysics*();
	};

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class CachedPlayerPatches
	class CachedPlayerPatches final
	{
	private:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] private class CacheLocalPlayerPatch
		class CacheLocalPlayerPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyTargetMethod] public static MethodBase TargetMethod()
			static MethodBase *TargetMethod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPostfix] public static void SetLocalPlayer()
			static void SetLocalPlayer();
		};

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.Awake))][HarmonyPostfix] public static void CachePlayerPatch(PlayerControl __instance)
		static void CachePlayerPatch(PlayerControl *__instance);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.OnDestroy))][HarmonyPostfix] public static void RemoveCachedPlayerPatch(PlayerControl __instance)
		static void RemoveCachedPlayerPatch(PlayerControl *__instance);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameData), nameof(GameData.Deserialize))][HarmonyPostfix] public static void AddCachedDataOnDeserialize()
		static void AddCachedDataOnDeserialize();

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameData), nameof(GameData.AddPlayer))][HarmonyPostfix] public static void AddCachedDataOnAddPlayer()
		static void AddCachedDataOnAddPlayer();

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.Deserialize))][HarmonyPostfix] public static void SetCachedPlayerId(PlayerControl __instance)
		static void SetCachedPlayerId(PlayerControl *__instance);
	};
}
