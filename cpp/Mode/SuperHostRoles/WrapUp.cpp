#include "WrapUp.h"
#include "FixedUpdate.h"
#include "../../BotManager.h"
#include "../../Roles/RoleClass.h"
#include "../../PlayerControlHepler.h"
#include "../../Roles/RoleHelper.h"
#include "../../Helpers/RPCHelper.h"
#include "Roles/BestFalseCharge.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Patch/PlayerControlPatch.h"
#include "../../EndGame/CustomEndReason.h"
#include "Chat.h"
#include "../../Helpers/MapUtilities.h"
#include "EndGameCheck.h"
#include "Roles/Jester.h"
#include "Roles/Nekomata.h"
#include "../../Roles/Nekomata.h"

using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void WrapUpClass::WrapUp(GameData::PlayerInfo *exiled)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		FixedUpdate::SetRoleNames();
		for (auto p : BotManager::AllBots)
		{
			p->RpcSetName(SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(p));
		}
		/*
		new LateTask(() =>
		{
		    foreach (PlayerControl p in CachedPlayer.AllPlayers)
		    {
		        byte reactorId = 3;
		        if (PlayerControl.GameOptions.MapId == 2) reactorId = 21;
		        MessageWriter MurderWriter = AmongUsClient.Instance.StartRpcImmediately(p.NetId, (byte)RpcCalls.MurderPlayer, SendOption.Reliable, p.getClientId());
		        MessageExtensions.WriteNetObject(MurderWriter, BotHandler.Bot);
		        AmongUsClient.Instance.FinishRpcImmediately(MurderWriter);
		        MessageWriter SabotageWriter = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, (byte)RpcCalls.RepairSystem, SendOption.Reliable, p.getClientId());
		        SabotageWriter.Write(reactorId);
		        MessageExtensions.WriteNetObject(SabotageWriter, p);
		        SabotageWriter.Write((byte)128);
		        AmongUsClient.Instance.FinishRpcImmediately(SabotageWriter);
		        MessageWriter SabotageFixWriter = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, (byte)RpcCalls.RepairSystem, SendOption.Reliable, p.getClientId());
		        SabotageFixWriter.Write(reactorId);
		        MessageExtensions.WriteNetObject(SabotageFixWriter, p);
		        SabotageFixWriter.Write((byte)16);
		        AmongUsClient.Instance.FinishRpcImmediately(SabotageFixWriter);
		        if (PlayerControl.GameOptions.MapId == 4)
		        {
		            MessageWriter SabotageFixWriter2 = AmongUsClient.Instance.StartRpcImmediately(MapUtilities.CachedShipStatus.NetId, (byte)RpcCalls.RepairSystem, SendOption.Reliable, p.getClientId());
		            SabotageFixWriter2.Write(reactorId);
		            MessageExtensions.WriteNetObject(SabotageFixWriter2, p);
		            SabotageFixWriter2.Write((byte)17);
		            AmongUsClient.Instance.FinishRpcImmediately(SabotageFixWriter2);
		        }
		    }
		}, 5f, "AntiBlack");*/
		for (auto p : RoleClass::RemoteSheriff::RemoteSheriffPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && !SuperNewRoles::PlayerControlHepler::IsMod(p))
			{
				SuperNewRoles::Helpers::RPCHelper::RpcResetAbilityCooldown(p);
			}
		}
		for (auto p : RoleClass::Arsonist::ArsonistPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && !SuperNewRoles::PlayerControlHepler::IsMod(p))
			{
				SuperNewRoles::Helpers::RPCHelper::RpcResetAbilityCooldown(p);
			}
		}
		AmongUsClient::Instance->StartCoroutine(L"ResetName");

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//		static System.Collections.IEnumerator ResetName()
	//			{
	//				yield return new WaitForSeconds(1);
	//				FixedUpdate.SetRoleNames();
	//			}
		Roles->BestFalseCharge::WrapUp();
		if (exiled == nullptr)
		{
			return;
		}
		if (exiled->Object.isRole(RoleId::Sheriff) || exiled->Object.isRole(RoleId::truelover) || exiled->Object.isRole(RoleId::MadMaker))
		{
			exiled->Object.RpcSetRoleDesync(RoleTypes::GuardianAngel);
		}
		if (RoleClass::Lovers::SameDie && exiled->Object.IsLovers())
		{
			if (AmongUsClient::Instance->AmHost)
			{
				PlayerControl *SideLoverPlayer = exiled->Object.GetOneSideLovers();
				if (SuperNewRoles::RoleHelpers::isAlive(SideLoverPlayer))
				{
					SuperNewRoles::Patches::CheckMurderPatch::RpcCheckExile(SideLoverPlayer);
				}
			}
		}
		if (exiled->Object.IsQuarreled())
		{
			if (AmongUsClient::Instance->AmHost)
			{
				auto Side = RoleHelpers::GetOneSideQuarreled(exiled->Object);
				if (SuperNewRoles::RoleHelpers::isDead(Side))
				{
					RPCProcedure::ShareWinner(exiled->Object.PlayerId);
					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
					Writer->Write(exiled->Object.PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
					Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
					Writer->Write(static_cast<unsigned char>(CustomGameOverReason::QuarreledWin));
					SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
					RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::QuarreledWin));
					auto winplayers = std::vector<PlayerControl*> {exiled->Object};
					//EndGameCheck.WinNeutral(winplayers);
					Chat::WinCond = CustomGameOverReason::QuarreledWin;
					Chat::Winner = {exiled->Object};
					RoleClass::Quarreled::IsQuarreledWin = true;
					EndGameCheck::CustomEndGame(MapUtilities::CachedShipStatus, GameOverReason::HumansByTask, false);
				}
			}
		}
		Roles->Jester::WrapUp(exiled);
		Roles->Nekomata::WrapUp(exiled);
	}
}
