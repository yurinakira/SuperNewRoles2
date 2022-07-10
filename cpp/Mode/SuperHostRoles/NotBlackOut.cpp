#include "NotBlackOut.h"
#include "../ModeHandler.h"
#include "../../PlayerControlHepler.h"
#include "../../ModHelpers.h"
#include "../../LateTask.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void NotBlackOut::CheckForEndVotingPatch::Prefix(MeetingHud *__instance)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::SuperHostRoles}))
		{
			EndMeetingPatch();
		}
	}

	void NotBlackOut::EndMeetingPatch()

	{
	/*
	    //霊界用暗転バグ対処
	    foreach (var pc in CachedPlayer.AllPlayers)
	        if (IsAntiBlackOut(pc) && pc.isDead()) pc.ResetPlayerCam(19f);*/
	}

	bool NotBlackOut::IsAntiBlackOut(PlayerControl *player)
	{
		if (SuperNewRoles::PlayerControlHepler::IsMod(player))
		{
			return false;
		}
		/*
		if (player.isRole(RoleId.Egoist)) return true;
		if (player.isRole(RoleId.Sheriff)) return true;
		if (player.isRole(RoleId.truelover)) return true;
		if (player.isRole(RoleId.FalseCharges)) return true;
		if (player.isRole(RoleId.RemoteSheriff)) return true;
		*/
		return false;
	}

	void NotBlackOut::ResetPlayerCam(PlayerControl *pc, float delay)
	{
		if (pc == nullptr || !AmongUsClient::Instance->AmHost || pc->AmOwner)
		{
			return;
		}
		int clientId = SuperNewRoles::ModHelpers::getClientId(pc);

		unsigned char reactorId = 3;
		if (PlayerControl::GameOptions->MapId == 2)
		{
			reactorId = 21;
		}
		new LateTask([&] ()
		{
			MessageWriter *MurderWriter = AmongUsClient::Instance->StartRpcImmediately(pc->NetId, static_cast<unsigned char>(RpcCalls::MurderPlayer), SendOption::Reliable, clientId);
			MessageExtensions::WriteNetObject(MurderWriter, pc);
			AmongUsClient::Instance->FinishRpcImmediately(MurderWriter);
		}, delay, L"Murder To Reset Cam");
		new LateTask([&] ()
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"SetDesyncSabotage");
			MessageWriter *SabotageWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, clientId);
			SabotageWriter->Write(reactorId);
			MessageExtensions::WriteNetObject(SabotageWriter, pc);
			SabotageWriter->Write(static_cast<unsigned char>(128));
			AmongUsClient::Instance->FinishRpcImmediately(SabotageWriter);
		}, delay, L"Reactor Desync");
		new LateTask([&] ()
		{
			MessageWriter *SabotageFixWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, clientId);
			SabotageFixWriter->Write(reactorId);
			MessageExtensions::WriteNetObject(SabotageFixWriter, pc);
			SabotageFixWriter->Write(static_cast<unsigned char>(16));
			AmongUsClient::Instance->FinishRpcImmediately(SabotageFixWriter);
		}, 0.1f + delay, L"Fix Desync Reactor");

		if (PlayerControl::GameOptions->MapId == 4) //Airship用
		{
			new LateTask([&] ()
			{
				MessageWriter *SabotageFixWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, clientId);
				SabotageFixWriter->Write(reactorId);
				MessageExtensions::WriteNetObject(SabotageFixWriter, pc);
				SabotageFixWriter->Write(static_cast<unsigned char>(17));
				AmongUsClient::Instance->FinishRpcImmediately(SabotageFixWriter);
			}, 0.1f + delay, L"Fix Desync Reactor 2");
		}
	}
}
