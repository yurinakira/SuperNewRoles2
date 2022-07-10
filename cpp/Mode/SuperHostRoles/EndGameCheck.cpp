//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "EndGameCheck.h"
#include "../PlusModeHandler.h"
#include "Chat.h"
#include "../../Patch/Chat.h"
#include "../../Roles/RoleClass.h"
#include "../../Roles/RoleHelper.h"
#include "../../Patch/TaskCount.h"
#include "../../EndGame/CustomEndReason.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../CustomRPC/CustomRPC.h"
#include "FixedUpdate.h"
#include "../../Patch/FixedUpdate.h"
#include "../../Helpers/RPCHelper.h"
#include "../../Roles/Demon.h"
#include "../../Roles/Arsonist.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	bool EndGameCheck::CheckEndGame(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (CheckAndEndGameForDefaultWin(__instance, statistics))
		{
			return false;
		}
		if (CheckAndEndGameForJackalWin(__instance, statistics))
		{
			return false;
		}
		if (CheckAndEndGameForSabotageWin(__instance))
		{
			return false;
		}
		if (!PlusModeHandler::isMode(PlusModeId::NotTaskWin) && CheckAndEndGameForTaskWin(__instance))
		{
			return false;
		}
		if (CheckAndEndGameForWorkpersonWin(__instance))
		{
			return false;
		}
		return false;
	}

	void EndGameCheck::WinNeutral(std::vector<PlayerControl*> &players)
	{
		/**
		foreach (PlayerControl p in CachedPlayer.AllPlayers)
		{
		    if (players.IsCheckListPlayerControl(p))
		    {
		        p.UnCheckedRpcSetRole(RoleTypes.Impostor);
		    } else
		    {
		        p.UnCheckedRpcSetRole(RoleTypes.Crewmate);
		    }
		}
		**/
	}

	void EndGameCheck::CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd)
	{
		Chat::IsOldSHR = true;
		std::vector<PlayerControl*> WinGods;
		for (auto p : RoleClass::God::GodPlayer)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p))
			{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(complate, all) = TaskCount.TaskDateNoClearCheck(p.Data);
				auto [complate, all] = TaskCount::TaskDateNoClearCheck(p->Data);
				if (!RoleClass::God::IsTaskEndWin || complate >= all)
				{
					if (WinGods.empty())
					{
						WinGods = std::vector<PlayerControl*>();
					}
					WinGods.push_back(p);
					Chat::WinCond = CustomGameOverReason::GodWin;
				}
			}
		}
		if (Chat::WinCond == CustomGameOverReason::GodWin)
		{
			WinNeutral(WinGods);
			Chat::Winner = WinGods;
		}
		for (auto p : RoleClass::Sheriff::SheriffPlayer)
		{
			p->RpcSetRole(RoleTypes::GuardianAngel);
		}
		for (auto p : RoleClass::RemoteSheriff::RemoteSheriffPlayer)
		{
			p->RpcSetRole(RoleTypes::GuardianAngel);
		}
		for (auto p : RoleClass::Arsonist::ArsonistPlayer)
		{
			p->RpcSetRole(RoleTypes::GuardianAngel);
		}
		if (!OnGameEndPatch::EndData && (reason == GameOverReason::ImpostorByKill || reason == GameOverReason::ImpostorBySabotage || reason == GameOverReason::ImpostorByVote || reason == GameOverReason::ImpostorDisconnect))
		{
			for (auto p : RoleClass::Survivor::SurvivorPlayer)
			{
				if (SuperNewRoles::RoleHelpers::isDead(p))
				{
					p->RpcSetRole(RoleTypes::GuardianAngel);
				}
			}
		}
		else if (OnGameEndPatch::EndData == CustomGameOverReason::JackalWin)
		{
			for (auto p : CachedPlayer::AllPlayers)
			{
				if (!SuperNewRoles::RoleHelpers::isRole(p, RoleId::Jackal))
				{
					p->RpcSetRole(RoleTypes::GuardianAngel);
				}
			}
		}
		FixedUpdate::SetRoleNames(true);
		__instance->enabled = false;
		ShipStatus::RpcEndGame(reason, showAd);
	}

	bool EndGameCheck::CheckAndEndGameForSabotageWin(ShipStatus *__instance)
	{
		if (__instance->Systems == nullptr)
		{
			return false;
		}
		ISystemType *systemType = __instance->Systems->ContainsKey(SystemTypes::LifeSupp) ? __instance->Systems[SystemTypes::LifeSupp] : nullptr;
		if (systemType != nullptr)
		{
			LifeSuppSystemType *lifeSuppSystemType = systemType->TryCast<LifeSuppSystemType*>();
			if (lifeSuppSystemType != nullptr && lifeSuppSystemType->Countdown < 0.0f)
			{
				EndGameForSabotage(__instance);
				lifeSuppSystemType->Countdown = 10000.0f;
				return true;
			}
		}
		ISystemType *systemType2 = __instance->Systems->ContainsKey(SystemTypes::Reactor) ? __instance->Systems[SystemTypes::Reactor] : nullptr;
		if (systemType2 == nullptr)
		{
			systemType2 = __instance->Systems->ContainsKey(SystemTypes::Laboratory) ? __instance->Systems[SystemTypes::Laboratory] : nullptr;
		}
		if (systemType2 != nullptr)
		{
			ICriticalSabotage *criticalSystem = systemType2->TryCast<ICriticalSabotage*>();
			if (criticalSystem != nullptr && criticalSystem->Countdown < 0.0f)
			{
				EndGameForSabotage(__instance);
				criticalSystem->ClearSabotage();
				return true;
			}
		}
		return false;
	}

	bool EndGameCheck::CheckAndEndGameForTaskWin(ShipStatus *__instance)
	{
		if (GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks) //&& Chat.WinCond == null)
		{
			Chat::WinCond = CustomGameOverReason::CrewmateWin;
			CustomEndGame(__instance, GameOverReason::HumansByTask, false);
			return true;
		}
		return false;
	}

	bool EndGameCheck::CheckAndEndGameForJackalWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (statistics->TeamJackalAlive >= statistics->TotalAlive - statistics->TeamJackalAlive && statistics->TeamImpostorsAlive == 0)
		{
			MessageWriter *Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
			Writer->Write(static_cast<unsigned char>(CustomGameOverReason::JackalWin));
			SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
			CustomRPC::RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::JackalWin));
			__instance->enabled = false;
			CustomEndGame(__instance, GameOverReason::ImpostorByKill, false);
			return true;
		}
		return false;
	}

	bool EndGameCheck::CheckAndEndGameForDefaultWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		int num1 = 0;
		int num2 = 0;
		int num3 = 0;
		for (int index = 0; index < GameData::Instance->PlayerCount; ++index)
		{
			GameData::PlayerInfo *allPlayer = GameData::Instance->AllPlayers[index];
			if (!allPlayer->Disconnected && allPlayer->Object.IsPlayer())
			{
				//インポスター判定ならnum3にカウント
				if (allPlayer->Object.isImpostor() || allPlayer->Object.isRole(RoleId::Egoist))
				{
					++num3;
				}
				//生存しているかつ
				if (!allPlayer->IsDead)
				{
					//インポスターならnum2に追加
					if (allPlayer->Object.isImpostor() || allPlayer->Object.isRole(RoleId::Egoist))
					{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
