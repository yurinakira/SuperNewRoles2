#pragma once

#include <string>
#include <limits>
#include "../stringhelper.h"

using namespace Assets::CoreScripts;
using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Helpers
{
	class AntiHackingBan
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetSkin))] class Setcolorskin
		class Setcolorskin
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string skinId)
			static bool Prefix(PlayerControl *__instance, std::wstring &skinId);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetHat))] class Sethat
		class Sethat
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string hatId)
			static bool Prefix(PlayerControl *__instance, std::wstring &hatId);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetVisor))] class SetVisor
		class SetVisor
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string visorId)
			static bool Prefix(PlayerControl *__instance, std::wstring &visorId);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSetPet))] class SetPet
		class SetPet
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] ref string petId)
			static bool Prefix(PlayerControl *__instance, std::wstring &petId);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcShapeshift))] class RpcShapeShiftPatch
		class RpcShapeShiftPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target, [HarmonyArgument(1)] bool shouldAnimate)
			static bool Prefix(PlayerControl *__instance, PlayerControl *target, bool shouldAnimate);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcMurderPlayer))] class RpcMurderPlayer
		class RpcMurderPlayer
		{
		public:
			static bool Prefix(PlayerControl *__instance, PlayerControl *target);
		};
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.RpcSendChat))] class RpcSendChatPatch
		class RpcSendChatPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, ref bool __result, [HarmonyArgument(0)] string chatText)
			static bool Prefix(PlayerControl *__instance, bool &__result, const std::wstring &chatText);
		};
	};
}
