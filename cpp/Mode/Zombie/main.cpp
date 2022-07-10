#include "main.h"
#include "../../Patch/TaskCount.h"
#include "ZombieOptions.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../SuperHostRoles/SyncSetting.h"
#include "../SuperHostRoles/FixedUpdate.h"
#include "FixedUpdate.h"
#include "../../Patch/FixedUpdate.h"
#include "../../Helpers/RPCHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{

Color *main::Zombiecolor = new Color32(143, 188, 143, std::numeric_limits<unsigned char>::max());
Color *main::Policecolor = Color::blue;
std::vector<int> main::ZombiePlayers;

	bool main::IsZombie(PlayerControl *player)
	{
		try
		{
			if (player->Data->Disconnected)
			{
				return true;
			}
			if (player->Data->Role.IsImpostor || std::find(ZombiePlayers.begin(), ZombiePlayers.end(), player->PlayerId) != ZombiePlayers.end())
			{
				return true;
			}
			return false;
		}
		catch (...)
		{
			return false;
		}
	}

	void main::CountTaskZombie(GameData *__instance)
	{
		__instance->TotalTasks = 0;
		__instance->CompletedTasks = 0;
		for (int i = 0; i < __instance->AllPlayers->Count; i++)
		{
			GameData::PlayerInfo *playerInfo = __instance->AllPlayers[i];
			if (!playerInfo->Object.IsZombie())
			{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(playerCompleted, playerTotal) = TaskCount.TaskDate(playerInfo);
				auto [playerCompleted, playerTotal] = TaskCount::TaskDate(playerInfo);
				__instance->TotalTasks += playerTotal;
				__instance->CompletedTasks += playerCompleted;
			}
		}
	}

	void main::SetZombie(PlayerControl *player)
	{
		//player.RpcSetHat("");
		/*
		player.RpcSetSkin("");
		*/
		player->RpcSetColor(2);
		/*
		player.UncheckSetVisor("visor_pk01_DumStickerVisor");
		*/

		for (PlayerTask *task : *player->myTasks)
		{
			task->Complete();
		}
		/*
		var Data = PlayerControl.GameOptions;
		Data.CrewLightMod = ZombieOptions.ZombieLight.getFloat();
		RPCHelper.RPCGameOptionsPrivate(Data,player);
		*/
		if (!std::find(ZombiePlayers.begin(), ZombiePlayers.end(), player->PlayerId) != ZombiePlayers.end())
		{
			ZombiePlayers.push_back(player->PlayerId);
		}
		ZombieOptions::ChengeSetting(player);
	}

	void main::SetNotZombie(PlayerControl *player)
	{
		if (std::find(ZombiePlayers.begin(), ZombiePlayers.end(), player->PlayerId) != ZombiePlayers.end())
		{
			ZombiePlayers.Remove(player->PlayerId);
		}
	}

	bool main::EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		bool IsZombieWin = true;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (!std::find(ZombiePlayers.begin(), ZombiePlayers.end(), p->PlayerId) != ZombiePlayers.end() && SuperNewRoles::RoleHelpers::isAlive(p))
			{
				IsZombieWin = false;
			}
		}
		if (IsZombieWin)
		{
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::ImpostorByKill, false);
			return true;
		}
		if (GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks)
		{
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::HumansByVote, false);
			return true;
		}
		return false;
	}

	void main::ClearAndReload()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			p->SetHat(L"", 0);
		}
		/*
		PlayerControl.GameOptions.ImpostorLightMod = ZombieOptions.ZombieLight.getFloat();
		CachedPlayer.LocalPlayer.PlayerControl.RpcSyncSettings(PlayerControl.GameOptions);
		*/
		SyncSetting::OptionData = PlayerControl::GameOptions;
		ZombieOptions::ZombieLight = ZombieOptions::ZombieLightOption->getFloat();
		ZombieOptions::ZombieSpeed = ZombieOptions::ZombieSpeedOption->getFloat();
		ZombieOptions::PoliceLight = ZombieOptions::PoliceLightOption->getFloat();
		ZombieOptions::PoliceSpeed = ZombieOptions::PoliceSpeedOption->getFloat();
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		ZombiePlayers = std::vector<int>();
		if (AmongUsClient::Instance->AmHost)
		{
			FixedUpdate::IsStart = false;
			for (auto p : CachedPlayer::AllPlayers)
			{
				SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(p);
				/*
				p.UncheckSetVisor("visor_EmptyVisor");
				*/

				//p.RpcSetHat("");

				/*
				p.RpcSetSkin("");
				*/
			}
		}
		ZombieOptions::FirstChangeSettings();
	}

	void main::SetTimer()
	{
		FixedUpdate::IsStart = true;
		for (auto p : CachedPlayer::AllPlayers)
		{
			for (auto p2 : CachedPlayer::AllPlayers)
			{
				if (p2->PlayerId != p->PlayerId)
				{
					SuperNewRoles::Helpers::RPCHelper::RpcSetNamePrivate(p2, L"Playing on SuperNewRoles!", p);
				}
			}
		}
		FixedUpdate::NameChangeTimer = ZombieOptions::StartSecondOption->getFloat();
	}
}
