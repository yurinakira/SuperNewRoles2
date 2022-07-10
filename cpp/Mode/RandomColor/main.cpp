#include "main.h"
#include "../PlusModeHandler.h"

namespace SuperNewRoles::Mode::RandomColor
{

	bool main::CheckEndGame(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (CheckAndEndGameForSabotageWin(__instance))
		{
			return false;
		}
		if (CheckAndEndGameForImpostorWin(__instance, statistics))
		{
			return false;
		}
		if (CheckAndEndGameForCrewmateWin(__instance, statistics))
		{
			return false;
		}
		if (!PlusModeHandler::isMode(PlusModeId::NotTaskWin) && CheckAndEndGameForTaskWin(__instance))
		{
			return false;
		}
		return false;
	}

	void main::CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd)
	{
		__instance->enabled = false;
		ShipStatus::RpcEndGame(reason, showAd);
	}

	bool main::CheckAndEndGameForSabotageWin(ShipStatus *__instance)
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

	bool main::CheckAndEndGameForTaskWin(ShipStatus *__instance)
	{
		if (GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks)
		{
			CustomEndGame(__instance, GameOverReason::HumansByTask, false);
			return true;
		}
		return false;
	}

	bool main::CheckAndEndGameForImpostorWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (statistics->TeamImpostorsAlive >= statistics->TotalAlive - statistics->TeamImpostorsAlive && statistics->TeamJackalAlive == 0)
		{
	//C# TO C++ CONVERTER TODO TASK: The following 'switch expression' was not converted by C# to C++ Converter:
	//				var endReason = TempData.LastDeathReason switch
	//				{
	//					DeathReason.Exile => GameOverReason.ImpostorByVote,
	//					DeathReason.Kill => GameOverReason.ImpostorByKill,
	//					_ => GameOverReason.ImpostorByVote,
	//				};
			CustomEndGame(__instance, endReason, false);
			return true;
		}
		return false;
	}

	bool main::CheckAndEndGameForCrewmateWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (statistics->CrewAlive > 0 && statistics->TeamImpostorsAlive == 0)
		{
			CustomEndGame(__instance, GameOverReason::HumansByVote, false);
			return true;
		}
		return false;
	}

	void main::EndGameForSabotage(ShipStatus *__instance)
	{
		CustomEndGame(__instance, GameOverReason::ImpostorBySabotage, false);
		return;
	}
}
