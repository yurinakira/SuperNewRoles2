#pragma once

#include "../CustomRPC/CustomRPCSender.h"
#include <string>
#include <vector>
#include <limits>

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace UnityEngine;
using namespace static MeetingHud;

namespace SuperNewRoles::Helpers
{
	class RPCHelper final
	{
	public:
		static MessageWriter *StartRPC(RpcCalls *RPCId, PlayerControl *SendTarget = nullptr);
		static MessageWriter *StartRPC(unsigned int NetId, RpcCalls *RPCId, PlayerControl *SendTarget = nullptr);
		static MessageWriter *StartRPC(CustomRPC::CustomRPC RPCId, PlayerControl *SendTarget = nullptr);
		static MessageWriter *StartRPC(unsigned int NetId, CustomRPC::CustomRPC RPCId, PlayerControl *SendTarget = nullptr);
		static MessageWriter *StartRPC(unsigned char RPCId, PlayerControl *SendTarget = nullptr);
		static MessageWriter *StartRPC(unsigned int NetId, unsigned char RPCId, PlayerControl *SendTarget = nullptr);
		static void EndRPC(MessageWriter *Writer);
		static void RPCGameOptionsPrivate(GameOptionsData *Data, PlayerControl *target);
		/// <summary>
		/// 特定のプレイヤーから見て、特定のプレイヤーの名前を変更する関数
		/// </summary>
		/// <param name="TargetPlayer">変更する名前</param>
		/// <param name="NewName">変更後の名前</param>
		/// <param name="SeePlayer">変更後の名前を見れるプレイヤー</param>
		static void RpcSetNamePrivate(PlayerControl *TargetPlayer, const std::wstring &NewName, PlayerControl *SeePlayer = nullptr);

		static void RpcSnapToPrivate(CustomNetworkTransform *__instance, Vector2 *position, PlayerControl *SeePlayer);

		static void RpcProtectPlayerPrivate(PlayerControl *SourcePlayer, PlayerControl *target, int colorId, PlayerControl *SeePlayer = nullptr);

		static void RpcProtectPlayerPrivate(PlayerControl *SourcePlayer, CustomRpcSender *sender, PlayerControl *target, int colorId, PlayerControl *SeePlayer = nullptr);

		static void RPCSendChatPrivate(PlayerControl *TargetPlayer, const std::wstring &Chat, PlayerControl *SeePlayer = nullptr);

		static void RpcVotingCompletePrivate(MeetingHud *__instance, std::vector<VoterState*> &states, GameData::PlayerInfo *exiled, bool tie, PlayerControl *SeePlayer);
		/// <summary>
		/// 通常のRPCのExiled
		/// </summary>
		static void RpcInnerExiled(PlayerControl *TargetPlayer);
		static void RPCSetColorModOnly(PlayerControl *player, unsigned char color);
		static void RPCSetRoleUnchecked(PlayerControl *player, RoleTypes *roletype);

		static void RpcResetAbilityCooldown(PlayerControl *target);
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(CustomNetworkTransform), nameof(CustomNetworkTransform.RpcSnapTo))] class RpcSnapToPatch
		class RpcSnapToPatch
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(CustomNetworkTransform __instance, [HarmonyArgument(0)] Vector2 position)
			static bool Prefix(CustomNetworkTransform *__instance, Vector2 *position);
		};
	};
}
