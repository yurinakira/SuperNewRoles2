#include "Arsonist.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"
#include "../Main.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../BotManager.h"
#include "RoleHelper.h"
#include "../ModHelpers.h"
#include "../Mode/ModeHandler.h"
#include "../Buttons/Buttons.h"
#include "../EndGame/CustomEndReason.h"
#include "../EndGame/FinalStatus.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Arsonist::ArsonistDouse(PlayerControl *target, PlayerControl *source)
	{
		try
		{
			if (source == nullptr)
			{
				source = PlayerControl::LocalPlayer;
			}
			MessageWriter *Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ArsonistDouse);
			Writer->Write(source->PlayerId);
			Writer->Write(target->PlayerId);
			SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
			RPCProcedure::ArsonistDouse(source->PlayerId, target->PlayerId);
		}
		catch (const std::runtime_error &e)
		{
			SuperNewRolesPlugin::Logger->LogError(e);
		}
	}

	std::vector<PlayerControl*> Arsonist::GetDouseData(PlayerControl *player)
	{
		return RoleClass::Arsonist::DouseDatas.find(player->PlayerId) != RoleClass::Arsonist::DouseDatas.end() ? RoleClass::Arsonist::DouseDatas[player->PlayerId] : std::vector<PlayerControl*>();
	}

	std::vector<PlayerControl*> Arsonist::GetUntarget()
	{
		if (RoleClass::Arsonist::DouseDatas.find(CachedPlayer::LocalPlayer->PlayerId) != RoleClass::Arsonist::DouseDatas.end())
		{
			return RoleClass::Arsonist::DouseDatas[CachedPlayer::LocalPlayer->PlayerId];
		}
		return std::vector<PlayerControl*>();
	}

	bool Arsonist::IsDoused(PlayerControl *source, PlayerControl *target)
	{
		if (source == nullptr || source->Data->Disconnected || target == nullptr || SuperNewRoles::RoleHelpers::isDead(target) || SuperNewRoles::BotManager::IsBot(target))
		{
			return true;
		}
		if (source->PlayerId == target->PlayerId)
		{
			return true;
		}
		if (RoleClass::Arsonist::DouseDatas.find(source->PlayerId) != RoleClass::Arsonist::DouseDatas.end())
		{
			if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Arsonist::DouseDatas[source->PlayerId], target))
			{
				return true;
			}
		}
		return false;
	}

	std::vector<PlayerControl*> Arsonist::GetIconPlayers(PlayerControl *player)
	{
		if (player == nullptr)
		{
			player = PlayerControl::LocalPlayer;
		}
		if (RoleClass::Arsonist::DouseDatas.find(player->PlayerId) != RoleClass::Arsonist::DouseDatas.end())
		{
			return RoleClass::Arsonist::DouseDatas[player->PlayerId];
		}
		return std::vector<PlayerControl*>();
	}

	bool Arsonist::IsViewIcon(PlayerControl *player)
	{
		if (player == nullptr)
		{
			return false;
		}
		for (auto data : RoleClass::Arsonist::DouseDatas)
		{
			for (PlayerControl *Player : data.Value)
			{
				if (player->PlayerId == Player->PlayerId)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Arsonist::IsButton()
	{
		return ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}) && RoleHelpers::isAlive(PlayerControl::LocalPlayer) && PlayerControl::LocalPlayer::isRole(RoleId::Arsonist);
	}

	bool Arsonist::IseveryButton()
	{
		return (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}) && RoleHelpers::isAlive(PlayerControl::LocalPlayer) && PlayerControl::LocalPlayer::isRole(RoleId::Arsonist)) || (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}) && RoleHelpers::isAlive(PlayerControl::LocalPlayer) && PlayerControl::LocalPlayer::isRole(RoleId::Arsonist));

	}

	bool Arsonist::IsWin(PlayerControl *Arsonist)
	{
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (player->PlayerId != Arsonist->PlayerId && !IsDoused(Arsonist, player))
			{
				return false;
			}
		}
		if (SuperNewRoles::RoleHelpers::isDead(Arsonist))
		{
			return false;
		}
		return true;
	}

	void Arsonist::HudManagerUpdatePatch::Postfix()
	{
		if (RoleClass::Arsonist::DouseTarget == nullptr)
		{
			return;
		}
		if (RoleClass::Arsonist::IsDouse)
		{
			if (!(RoleClass::Arsonist::DouseTarget == HudManagerStartPatch::setTarget(Arsonist::GetUntarget(), false)))
			{
				RoleClass::Arsonist::IsDouse = false;
				HudManagerStartPatch::ArsonistDouseButton->Timer = 0;
				SuperNewRolesPlugin::Logger->LogInfo(L"アーソ二ストが塗るのをやめた");
				return;
			}
			if (HudManagerStartPatch::ArsonistDouseButton->Timer <= 0.1f)
			{
				HudManagerStartPatch::ArsonistDouseButton->MaxTimer = RoleClass::Arsonist::CoolTime;
				HudManagerStartPatch::ArsonistDouseButton->Timer = HudManagerStartPatch::ArsonistDouseButton->MaxTimer;
				HudManagerStartPatch::ArsonistDouseButton->actionButton->cooldownTimerText->color = Color::white;
				SuperNewRoles::Roles::Arsonist::ArsonistDouse(RoleClass::Arsonist::DouseTarget);
				SuperNewRolesPlugin::Logger->LogInfo(L"アーソ二ストが塗った:" + RoleClass::Arsonist::DouseTarget);
			}
		}
	}

	bool Arsonist::IsArsonistWinFlag()
	{
		for (auto player : RoleClass::Arsonist::ArsonistPlayer)
		{
			if (IsWin(player))
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"アーソニストが勝利条件を達成");
				return true;
			}
		}
		return false;
	}

	bool Arsonist::CheckAndEndGameForArsonistWin(ShipStatus *__instance)
	{
		if (RoleClass::Arsonist::TriggerArsonistWin)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"CheckAndEndGame");
			__instance->enabled = false;
			ShipStatus::RpcEndGame(static_cast<GameOverReason*>(CustomGameOverReason::ArsonistWin), false);
			return true;
		}
		return false;
	}

	void Arsonist::SetWinArsonist()
	{
		RoleClass::Arsonist::TriggerArsonistWin = true;
	}

std::unordered_map<unsigned char, float> Arsonist::ArsonistTimer;

	void Arsonist::ArsonistFinalStatus(PlayerControl *__instance)
	{
		if (RoleClass::Arsonist::TriggerArsonistWin)
		{
			FinalStatusPatch::FinalStatusData::FinalStatuses[__instance->PlayerId] = FinalStatus::Ignite;
		}
	}
}
