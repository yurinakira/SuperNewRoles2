#pragma once

using namespace HarmonyLib;
using namespace InnerNet;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class Usables
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.OnPlayerLeft))] class OnPlayerLeftPatch
		class OnPlayerLeftPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(AmongUsClient __instance, [HarmonyArgument(0)] ClientData data, [HarmonyArgument(1)] DisconnectReasons reason)
			static void Postfix(AmongUsClient *__instance, ClientData *data, DisconnectReasons *reason);
		};

	};
}
