#pragma once

#include "SuperNewRoles.CustomCosmetics.ShareCosmetics.CosmeticsObject.h"
#include <string>
#include <unordered_map>

using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics::ShareCosmetics
{
	class SharePatch
	{
	public:
		static std::unordered_map<int, std::wstring> PlayerUrl;
		static std::unordered_map<int, std::wstring> PlayerDatas;
		static std::unordered_map<int, CosmeticsObject*> PlayerObjects;
		/*
		[HarmonyPatch(typeof(AmongUsClient), nameof(AmongUsClient.OnPlayerJoined))]
		public class AmongUsClientOnPlayerJoinedPatch
		{
		    public static void Postfix()
		    {
		        return;
		        if (PlayerControl.LocalPlayer != null && ConfigRoles.IsShareCosmetics.Value && ConfigRoles.ShareCosmeticsNamePlatesURL.Value != "")
		        {
		            MessageWriter writer = AmongUsClient.Instance.StartRpcImmediately(PlayerControl.LocalPlayer.NetId, (byte)CustomRPC.CustomRPC.ShareCosmetics, Hazel.SendOption.Reliable, -1);
		            writer.Write((byte)CachedPlayer.LocalPlayer.PlayerId);
		            writer.Write(ConfigRoles.ShareCosmeticsNamePlatesURL.Value);
		            AmongUsClient.Instance.FinishRpcImmediately(writer);
		            CustomRPC.RPCProcedure.ShareCosmetics(
		                (byte)CachedPlayer.LocalPlayer.PlayerId,
		                ConfigRoles.ShareCosmeticsNamePlatesURL.Value
		                );
		        }
		    }
		}
		*/
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameStartManager), nameof(GameStartManager.Update))] public class GameStartManagerUpdatePatch
		class GameStartManagerUpdatePatch
		{
		public:
			static int Proce;
			static void Postfix(GameStartManager *__instance);
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
	};
}
