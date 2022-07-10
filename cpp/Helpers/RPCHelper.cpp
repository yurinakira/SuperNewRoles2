//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "RPCHelper.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace UnityEngine;
using namespace static MeetingHud;

namespace SuperNewRoles::Helpers
{

	MessageWriter *RPCHelper::StartRPC(RpcCalls *RPCId, PlayerControl *SendTarget)
	{
		return StartRPC(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(RPCId), SendTarget);
	}

	MessageWriter *RPCHelper::StartRPC(unsigned int NetId, RpcCalls *RPCId, PlayerControl *SendTarget)
	{
		return StartRPC(NetId, static_cast<unsigned char>(RPCId), SendTarget);
	}

	MessageWriter *RPCHelper::StartRPC(CustomRPC::CustomRPC RPCId, PlayerControl *SendTarget)
	{
		return StartRPC(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(RPCId), SendTarget);
	}

	MessageWriter *RPCHelper::StartRPC(unsigned int NetId, CustomRPC::CustomRPC RPCId, PlayerControl *SendTarget)
	{
		return StartRPC(NetId, static_cast<unsigned char>(RPCId), SendTarget);
	}

	MessageWriter *RPCHelper::StartRPC(unsigned char RPCId, PlayerControl *SendTarget)
	{
		return StartRPC(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(RPCId), SendTarget);
	}

	MessageWriter *RPCHelper::StartRPC(unsigned int NetId, unsigned char RPCId, PlayerControl *SendTarget)
	{
		auto target = SendTarget != nullptr ? SuperNewRoles::ModHelpers::getClientId(SendTarget) : -1;
		return AmongUsClient::Instance->StartRpcImmediately(NetId, RPCId, Hazel::SendOption::Reliable, target);
	}

	void RPCHelper::EndRPC(MessageWriter *Writer)
	{
		AmongUsClient::Instance->FinishRpcImmediately(Writer);
	}

	void RPCHelper::RPCGameOptionsPrivate(GameOptionsData *Data, PlayerControl *target)
	{
		MessageWriter *messageWriter = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(2), Hazel::SendOption::None, SuperNewRoles::ModHelpers::getClientId(target));
		messageWriter->WriteBytesAndSize(Data->ToBytes(static_cast<unsigned char>(5)));
		messageWriter->EndMessage();
	}

	void RPCHelper::RpcSetNamePrivate(PlayerControl *TargetPlayer, const std::wstring &NewName, PlayerControl *SeePlayer)
	{
		if (TargetPlayer == nullptr || NewName == L"" || !AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (SeePlayer == nullptr)
		{
			SeePlayer = TargetPlayer;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(SeePlayer);
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(TargetPlayer->NetId, static_cast<unsigned char>(RpcCalls::SetName), SendOption::Reliable, clientId);
		writer->Write(NewName);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
	}

	void RPCHelper::RpcSnapToPrivate(CustomNetworkTransform *__instance, Vector2 *position, PlayerControl *SeePlayer)
	{
		unsigned short minSid = static_cast<unsigned short>(__instance->lastSequenceId + 5);
		MessageWriter *val = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, 21, SendOption::None, SuperNewRoles::ModHelpers::getClientId(SeePlayer));
		__instance->WriteVector2(position, val);
		val->Write(__instance->lastSequenceId);
		val->EndMessage();
	}

	void RPCHelper::RpcProtectPlayerPrivate(PlayerControl *SourcePlayer, PlayerControl *target, int colorId, PlayerControl *SeePlayer)
	{
		if (SourcePlayer == nullptr || target == nullptr || !AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (SeePlayer == nullptr)
		{
			SeePlayer = SourcePlayer;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(SeePlayer);
		MessageWriter *val = AmongUsClient::Instance->StartRpcImmediately(SourcePlayer->NetId, static_cast<unsigned char>(RpcCalls::ProtectPlayer), SendOption::Reliable, clientId);
		val->WriteNetObject(target);
		val->Write(colorId);
		AmongUsClient::Instance->FinishRpcImmediately(val);
	}

	void RPCHelper::RpcProtectPlayerPrivate(PlayerControl *SourcePlayer, CustomRpcSender *sender, PlayerControl *target, int colorId, PlayerControl *SeePlayer)
	{
		if (SourcePlayer == nullptr || target == nullptr || !AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (SeePlayer == nullptr)
		{
			SeePlayer = SourcePlayer;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(SeePlayer);
		sender->StartMessage(clientId)->StartRpc(SourcePlayer->NetId, RpcCalls::ProtectPlayer).WriteNetObject(target).Write(colorId).EndRpc().EndMessage();
	}

	void RPCHelper::RPCSendChatPrivate(PlayerControl *TargetPlayer, const std::wstring &Chat, PlayerControl *SeePlayer)
	{
		if (TargetPlayer == nullptr || Chat == L"")
		{
			return;
		}
		if (SeePlayer == nullptr)
		{
			SeePlayer = TargetPlayer;
		}
		auto clientId = SuperNewRoles::ModHelpers::getClientId(SeePlayer);
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(TargetPlayer->NetId, static_cast<unsigned char>(RpcCalls::SendChat), SendOption::None, clientId);
		writer->Write(Chat);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
	}

	void RPCHelper::RpcVotingCompletePrivate(MeetingHud *__instance, std::vector<VoterState*> &states, GameData::PlayerInfo *exiled, bool tie, PlayerControl *SeePlayer)
	{
		MessageWriter *val = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, 23, SendOption::None, SuperNewRoles::ModHelpers::getClientId(SeePlayer));
		val->WritePacked(states.size());
		for (auto voterState : states)
		{
			voterState->Serialize(val);
		}
		val->Write(exiled == nullptr ? nullptr : ((exiled->PlayerId != nullptr) ? exiled->PlayerId : std::numeric_limits<unsigned char>::max()));
		val->Write(tie);
		val->EndMessage();
	}

	void RPCHelper::RpcInnerExiled(PlayerControl *TargetPlayer)
	{
		if (TargetPlayer == nullptr)
		{
			return;
		}
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(TargetPlayer->NetId, static_cast<unsigned char>(RpcCalls::Exiled), Hazel::SendOption::None);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		TargetPlayer->Exiled();
	}

	void RPCHelper::RPCSetColorModOnly(PlayerControl *player, unsigned char color)
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(player->NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::UncheckedSetColor), SendOption::Reliable);
		writer->Write(color);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		player->SetColor(color);
	}

	void RPCHelper::RPCSetRoleUnchecked(PlayerControl *player, RoleTypes *roletype)
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::UncheckedSetVanilaRole), SendOption::Reliable);
		writer->Write(player->PlayerId);
		writer->Write(static_cast<unsigned char>(roletype));
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::UncheckedSetVanilaRole(player->PlayerId, static_cast<unsigned char>(roletype));
	}

	void RPCHelper::RpcResetAbilityCooldown(PlayerControl *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (PlayerControl::LocalPlayer->PlayerId == target->PlayerId)
		{
			PlayerControl::LocalPlayer::Data->Role.SetCooldown();
		}
		else
		{
			MessageWriter *writer = StartRPC(target->NetId, RpcCalls::ProtectPlayer, target);
			writer->Write(0);
			writer->Write(0);

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
