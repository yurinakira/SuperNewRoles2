#pragma once

#include <string>
#include <cmath>
#include "../stringhelper.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;

namespace SuperNewRoles::Patch
{
	class ChatCommand
	{
	};
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class DynamicLobbies
	class DynamicLobbies final
	{
	public:
		static int LobbyLimit;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ChatController), nameof(ChatController.SendChat))] private static class SendChatPatch
		class SendChatPatch final
		{
		private:
			static bool Prefix(ChatController *__instance);
		public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(InnerNetClient), nameof(InnerNetClient.HostGame))] public static class InnerNetClientHostPatch
			class InnerNetClientHostPatch final
			{
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(InnerNet.InnerNetClient __instance, [HarmonyArgument(0)] GameOptionsData settings)
				static void Prefix(InnerNet::InnerNetClient *__instance, GameOptionsData *settings);
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(InnerNet.InnerNetClient __instance, [HarmonyArgument(0)] GameOptionsData settings)
				static void Postfix(InnerNet::InnerNetClient *__instance, GameOptionsData *settings);
			};
		public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(InnerNetClient), nameof(InnerNetClient.JoinGame))] public static class InnerNetClientJoinPatch
			class InnerNetClientJoinPatch final
			{
			public:
				static void Prefix(InnerNet::InnerNetClient *__instance);
			};
		public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.OnPlayerJoined))] public static class AmongUsClientOnPlayerJoined
			class AmongUsClientOnPlayerJoined final
			{
			public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(AmongUsClient __instance, [HarmonyArgument(0)] ClientData client)
				static bool Prefix(AmongUsClient *__instance, ClientData *client);

			private:
				static void DisconnectPlayer(InnerNetClient *_this, int clientId);
			};
		};
	};
}
