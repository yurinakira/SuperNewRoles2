#include "WrapUpPatch.h"
#include "../Roles/RoleClass.h"
#include "../Roles/FalseCharges.h"
#include "../Mode/ModeHandler.h"
#include "../Sabotage/SabotageManager.h"
#include "../Sabotage/CognitiveDeficit/main.h"
#include "../EndGame/FinalStatus.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"
#include "../Roles/Kunoichi.h"
#include "../Roles/SerialKiller.h"
#include "../Roles/Assassin.h"
#include "../Roles/CountChanger.h"
#include "../Buttons/CustomButton.h"
#include "../PlayerControlHepler.h"
#include "../LateTask.h"
#include "../Mode/SuperHostRoles/WrapUp.h"
#include "../Roles/Seer.h"
#include "../Roles/RedRidingHood.h"
#include "../Roles/Nekomata.h"
#include "../ModHelpers.h"
#include "../Roles/RoleHelper.h"
#include "../Roles/EvilEraser.h"
#include "../EndGame/CustomEndReason.h"
#include "../EndGame/EndGame.h"
#include "TaskCount.h"
#include "../Sabotage/Patch.h"
#include "../Mode/SuperHostRoles/main.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;

namespace SuperNewRoles::Patch
{

	void WrapUpPatch::ExileControllerWrapUpPatch::Prefix(ExileController *__instance)
	{
		WrapUpPatch::Prefix(__instance->exiled);
	}

	void WrapUpPatch::ExileControllerWrapUpPatch::Postfix(ExileController *__instance)
	{
		WrapUpPatch::Postfix(__instance->exiled);
	}

	void WrapUpPatch::AirshipExileControllerWrapUpPatch::Prefix(AirshipExileController *__instance)
	{
		WrapUpPatch::Prefix(__instance->exiled);
	}

	void WrapUpPatch::AirshipExileControllerWrapUpPatch::Postfix(AirshipExileController *__instance)
	{
		WrapUpPatch::Postfix(__instance->exiled);
	}

	void WrapUpPatch::Prefix(GameData::PlayerInfo *exiled)
	{
		RoleClass::IsCoolTimeSetted = false;
		if (exiled != nullptr)
		{
			FalseCharges::WrapUp(exiled->Object);
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (SabotageManager::thisSabotage == SabotageManager::CustomSabotage::CognitiveDeficit)
			{
				if (!Sabotage::CognitiveDeficit::main::IsLocalEnd)
				{
					Sabotage::CognitiveDeficit::main::UpdateTime = 0;
				}
			}
			if (exiled == nullptr)
			{
				return;
			}
			FinalStatusPatch::FinalStatusData::FinalStatuses[exiled->Object.PlayerId] = FinalStatus::Exiled;
			if (exiled->Object.PlayerId != CachedPlayer::LocalPlayer->PlayerId)
			{
				return;
			}
			if (exiled->Object.isRole(RoleId::SideKiller))
			{
				auto sideplayer = RoleClass::SideKiller::getSidePlayer(PlayerControl::LocalPlayer);
				if (sideplayer != nullptr)
				{
					if (!RoleClass::SideKiller::IsUpMadKiller)
					{
						SuperNewRoles::Helpers::RPCHelper::RPCSetRoleUnchecked(sideplayer, RoleTypes::Impostor);
						RoleClass::SideKiller::IsUpMadKiller = true;
					}
				}
			}
		}
	}

	void WrapUpPatch::Postfix(GameData::PlayerInfo *exiled)
	{
		Kunoichi::WrapUp();
		SerialKiller::WrapUp();
		Assassin::WrapUp(exiled);
		CountChanger::CountChangerPatch::WrapUpPatch();
		CustomButton::MeetingEndedUpdate();

		PlayerControlHepler::refreshRoleDescription(PlayerControl::LocalPlayer);
		new LateTask([&] ()
		{
			RoleClass::IsMeeting = false;
		}, 0.1f, L"SetIsMeeting");
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			Mode::SuperHostRoles::WrapUpClass::WrapUp(exiled);
		}
		ModeHandler::Wrapup(exiled);
		if (exiled == nullptr)
		{
			return;
		}

		Seer::ExileControllerWrapUpPatch::WrapUpPostfix(exiled);
		RedRidingHood::WrapUp(exiled);
		Nekomata::NekomataEnd(exiled);

		exiled->Object.Exiled();
		exiled->IsDead = true;
		FinalStatusPatch::FinalStatusData::FinalStatuses[exiled->PlayerId] = FinalStatus::Exiled;
		auto Player = ModHelpers::playerById(exiled->PlayerId);
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (RoleClass::Lovers::SameDie && SuperNewRoles::RoleHelpers::IsLovers(Player))
			{
				if (AmongUsClient::Instance->AmHost)
				{
					PlayerControl *SideLoverPlayer = SuperNewRoles::RoleHelpers::GetOneSideLovers(Player);
					if (SuperNewRoles::RoleHelpers::isAlive(SideLoverPlayer))
					{
						MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::RPCMurderPlayer), Hazel::SendOption::Reliable, -1);
						writer->Write(SideLoverPlayer->PlayerId);
						writer->Write(SideLoverPlayer->PlayerId);
						writer->Write(std::numeric_limits<unsigned char>::max());
						AmongUsClient::Instance->FinishRpcImmediately(writer);
						RPCProcedure::RPCMurderPlayer(SideLoverPlayer->PlayerId, SideLoverPlayer->PlayerId, std::numeric_limits<unsigned char>::max());
					}
				}
			}
			EvilEraser::IsWinGodGuard = false;
			EvilEraser::IsWinFoxGuard = false;
			if (RoleHelpers::IsQuarreled(Player))
			{
				auto Side = RoleHelpers::GetOneSideQuarreled(Player);
				if (SuperNewRoles::RoleHelpers::isDead(Side))
				{
					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
					Writer->Write(Player->PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
					CustomRPC::RPCProcedure::ShareWinner(Player->PlayerId);
					RoleClass::Quarreled::IsQuarreledWin = true;
					CheckGameEndPatch::CustomEndGame(static_cast<GameOverReason*>(CustomGameOverReason::QuarreledWin), false);
				}
			}

			if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Jester::JesterPlayer, Player))
			{

				if (!RoleClass::Jester::IsJesterTaskClearWin || (Roles->RoleClass.Jester::IsJesterTaskClearWin && std::get<1>(Patch::TaskCount::TaskDateNoClearCheck(Player->Data)) - std::get<0>(Patch::TaskCount::TaskDateNoClearCheck(Player->Data)) == 0))
				{
					RPCProcedure::ShareWinner(Player->PlayerId);

					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
					Writer->Write(Player->PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
					Roles->RoleClass.Jester::IsJesterWin = true;
					CheckGameEndPatch::CustomEndGame(static_cast<GameOverReason*>(CustomGameOverReason::JesterWin), false);
				}
			}

			if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::MadJester::MadJesterPlayer, Player))
			{
				if (!RoleClass::MadJester::IsMadJesterTaskClearWin || (RoleClass::MadJester::IsMadJesterTaskClearWin && std::get<1>(TaskCount::TaskDateNoClearCheck(Player->Data)) - std::get<0>(TaskCount::TaskDateNoClearCheck(Player->Data)) == 0))
				{
					RPCProcedure::ShareWinner(Player->PlayerId);
					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
					Writer->Write(Player->PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
					Roles->RoleClass.MadJester::IsMadJesterWin = true;
					CheckGameEndPatch::CustomEndGame(static_cast<GameOverReason*>(CustomGameOverReason::MadJesterWin), false);
				}
			}
		}
		Mode::SuperHostRoles::main::RealExiled = nullptr;
	}
}
