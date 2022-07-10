#pragma once

#include "../MapCustom.h"
#include <vector>
#include <limits>

using namespace BepInEx::IL2CPP::Utils;
using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::MapCustoms;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.MapCustoms.MapCustom;
using namespace TMPro;
using namespace UnityEngine;

namespace SuperNewRoles::MapCustoms::Airship
{
	class SecretRoom final
	{
	public:
		static PlayerControl *leftplayer;
		static PlayerControl *rightplayer;

	private:
		static PoolablePlayer *left;
		static PoolablePlayer *right;
	public:
		static PlayerControl *UsePlayer;
		static bool IsWait;
		static TextMeshPro *LowerInfoText;
	private:
		static std::vector<Vector2*> TeleportPositions;

	public:
		enum class Status
		{
			UseConsole,
			CloseConsole,
			Join,
			Break,
			Wait,
			Teleport
		};

	public:
		static void SetSecretRoomTeleportStatus(Status status, unsigned char data1, unsigned char data2);
		static void Reset();
		static void ShipStatusAwake(ShipStatus *__instance);

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(VitalsMinigame), nameof(VitalsMinigame.Update))] public static class VitalsMinigameUpdate
		class VitalsMinigameUpdate final
		{
		public:
			static void Postfix(VitalsMinigame *__instance);
		};
	private:
		static bool onTask;
	public:
		static DateTime lastUpdate;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(VitalsMinigame), nameof(VitalsMinigame.Begin))] class VitalsMinigameStartPatch
		class VitalsMinigameStartPatch
		{
		private:
			static void Postfix(VitalsMinigame *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Console), nameof(Console.Use))] public static class ConsoleUsePatch
		class ConsoleUsePatch final
		{
		public:
			static bool Prefix(Console *__instance);
		private:
			static System::Collections::IEnumerator *Escape(Console *__instance, Coroutine *coro);
			/*
			static IEnumerator Move(Console __instance)
			{
			    float num = 24f;
			    PlayerPhysics myPhysics = PlayerControl.LocalPlayer.MyPhysics;
			    Vector2 val = __instance.name.Contains("2") ? new Vector2(0.14f, -5.025f) : __instance.transform.position;
			    Vector2 val2 = Vector2.left.Rotate(PlayerControl.LocalPlayer.PlayerId * num);
			    val += val2 / 2f;
			    Camera.main.GetComponent<FollowerCamera>().Locked = false;
			    yield return myPhysics.WalkPlayerTo(val, 0.001f);
			    yield return (object)new WaitForSeconds(0.1f);
			    Camera.main.GetComponent<FollowerCamera>().Locked = true;
			}
			*/

			static System::Collections::IEnumerator *Move2(Console *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(Console), nameof(Console.CanUse))] public static class ConsoleCanUsePatch
		class ConsoleCanUsePatch final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ref float __result, Console __instance, [HarmonyArgument(0)] GameData.PlayerInfo pc, [HarmonyArgument(1)] out bool canUse, [HarmonyArgument(2)] out bool couldUse)
			static bool Prefix(float &__result, Console *__instance, GameData::PlayerInfo *pc, bool &canUse, bool &couldUse);
		};
	private:
		static void ViewMinigame();
		static Console *ActivateConsole(GameObject *obj, float Distance = 1.7f);
	};
}
