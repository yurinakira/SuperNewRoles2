#pragma once

#include "ChatHandler.h"
#include <string>
#include <unordered_map>
#include "../stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace SuperNewRoles::Patch { class PlayerVersion; }

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Update))] public static class PlayerCountChange
	class PlayerCountChange final
	{
	public:
		static void Prefix(GameStartManager *__instance);
	};
	class ShareGameVersion
	{
	public:
		static bool IsVersionOK;
		static bool IsChangeVersion;
		static bool IsRPCSend;
		static float timer;
		static float RPCTimer;
	private:
		static bool notcreateroom;
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.OnPlayerJoined))] public class AmongUsClientOnPlayerJoinedPatch
		class AmongUsClientOnPlayerJoinedPatch
		{
		public:
			static void Postfix();
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Start))] public class GameStartManagerStartPatch
		class GameStartManagerStartPatch
		{
		public:
			static void Postfix();
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Update))] public class GameStartManagerUpdatePatch
		class GameStartManagerUpdatePatch
		{
		private:
			static bool update;
		public:
			static std::unordered_map<int, PlayerVersion*> VersionPlayers;
			static int Proce;
		private:
			static std::wstring currentText;
		public:
			static bool LastBlockStart;

			static void Prefix(GameStartManager *__instance);
			static void Postfix(GameStartManager *__instance);
			/**
			    if (!AmongUsClient.Instance.AmHost)
			    {
			        if (!playerVersions.ContainsKey(AmongUsClient.Instance.HostId) || SuperNewRolesPlugin.Version.CompareTo(playerVersions[AmongUsClient.Instance.HostId].version) != 0)
			        {
			            __instance.GameStartText.text = ModTranslation.getString("ErrorHostNoVersion");
			            __instance.GameStartText.transform.localPosition = __instance.StartButton.transform.localPosition + Vector3.up * 2;
			        }
			        else
			        {
			            __instance.GameStartText.transform.localPosition = __instance.StartButton.transform.localPosition;
			        }
			    }**/
		};
	};
	class PlayerVersion
	{
	public:
		Version *const version;
		const Guid guid;

		virtual ~PlayerVersion()
		{
			delete version;
		}

		PlayerVersion(Version *version, Guid guid);

		bool GuidMatches();
	};
}
