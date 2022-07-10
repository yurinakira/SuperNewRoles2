#pragma once

#include "FixedUpdate.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::MapOptions;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class BlockTool
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.RepairSystem))] class RepairSystemPatch
		class RepairSystemPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
			static void Prefix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount);
		};
	public:
		static std::vector<unsigned char> CameraPlayers;
		static std::vector<unsigned char> OldDesyncCommsPlayers;
	private:
		static float UsableDistance;
		static int Count;
	public:
		static bool IsCom;
		static float CameraTime;
		static float AdminTime;
		static float VitalTime;
		static void FixedUpdate();
		static Vector2 *GetAdminTransform();

		static Vector2 *GetCameraTransform();
		static Vector2 *GetVitalOrDoorLogTransform();
	};
}
