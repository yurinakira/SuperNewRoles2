#include "Usables.h"

using namespace HarmonyLib;
using namespace InnerNet;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(AmongUsClient __instance, [HarmonyArgument(0)] ClientData data, [HarmonyArgument(1)] DisconnectReasons reason)
	void Usables::OnPlayerLeftPatch::Postfix(AmongUsClient *__instance, ClientData *data, DisconnectReasons *reason)
	{
		if (AmongUsClient::Instance->GameState == InnerNetClient::GameStates::Started)
		{
		}
	}
}
