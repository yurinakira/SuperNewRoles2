#include "WinCheck.h"
#include "../PlusModeHandler.h"
#include "main.h"

namespace SuperNewRoles::Mode::NotImpostorCheck
{

	bool WinCheck::CheckEndGame(ShipStatus *__instance)
	{
		auto statistics = new PlayerStatistics(__instance);
		if (CheckAndEndGameForSabotageWin(__instance))
		{
			delete statistics;
			return false;
		}
		if (CheckAndEndGameForImpostorWin(__instance, statistics))
		{
//C# TO C++ CONVERTER TODO TASK: A 'delete statistics' statement was not added since statistics was passed to a method or constructor. Handle memory management manually.
			return false;
		}
		if (CheckAndEndGameForCrewmateWin(__instance, statistics))
		{
//C# TO C++ CONVERTER TODO TASK: A 'delete statistics' statement was not added since statistics was passed to a method or constructor. Handle memory management manually.
			return false;
		}
		if (!PlusModeHandler::isMode(PlusModeId::NotTaskWin) && CheckAndEndGameForTaskWin(__instance))
		{
//C# TO C++ CONVERTER TODO TASK: A 'delete statistics' statement was not added since statistics was passed to a method or constructor. Handle memory management manually.
			return false;
		}

//C# TO C++ CONVERTER TODO TASK: A 'delete statistics' statement was not added since statistics was passed to a method or constructor. Handle memory management manually.
		return false;
	}

	void WinCheck::CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd)
	{
		__instance->enabled = false;
		ShipStatus::RpcEndGame(reason, showAd);
	}

	bool WinCheck::CheckAndEndGameForSabotageWin(ShipStatus *__instance)
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

	bool WinCheck::CheckAndEndGameForTaskWin(ShipStatus *__instance)
	{
		if (GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks)
		{
			CustomEndGame(__instance, GameOverReason::HumansByTask, false);
			return true;
		}
		return false;
	}

	bool WinCheck::CheckAndEndGameForImpostorWin(ShipStatus *__instance, PlayerStatistics *statistics)
	{
		if (statistics->getTeamImpostorsAlive() >= statistics->getTotalAlive() - statistics->getTeamImpostorsAlive())
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

	bool WinCheck::CheckAndEndGameForCrewmateWin(ShipStatus *__instance, PlayerStatistics *statistics)
	{
		if (statistics->getCrewAlive() > 0 && statistics->getTeamImpostorsAlive() == 0)
		{
			CustomEndGame(__instance, GameOverReason::HumansByVote, false);
			return true;
		}
		return false;
	}

	void WinCheck::EndGameForSabotage(ShipStatus *__instance)
	{
		CustomEndGame(__instance, GameOverReason::ImpostorBySabotage, false);
		return;
	}

	int WinCheck::PlayerStatistics::getTeamImpostorsAlive() const
	{
		return TeamImpostorsAlive;
	}

	void WinCheck::PlayerStatistics::setTeamImpostorsAlive(int value)
	{
		TeamImpostorsAlive = value;
	}

	int WinCheck::PlayerStatistics::getCrewAlive() const
	{
		return CrewAlive;
	}

	void WinCheck::PlayerStatistics::setCrewAlive(int value)
	{
		CrewAlive = value;
	}

	int WinCheck::PlayerStatistics::getTotalAlive() const
	{
		return TotalAlive;
	}

	void WinCheck::PlayerStatistics::setTotalAlive(int value)
	{
		TotalAlive = value;
	}

	WinCheck::PlayerStatistics::PlayerStatistics(ShipStatus *__instance)
	{
		GetPlayerCounts();
	}

	void WinCheck::PlayerStatistics::GetPlayerCounts()
	{
		int numImpostorsAlive = 0;
		int numCrewAlive = 0;
		int numTotalAlive = 0;

		for (int i = 0; i < GameData::Instance->PlayerCount; i++)
		{
			GameData::PlayerInfo *playerInfo = GameData::Instance->AllPlayers[i];
			if (!playerInfo->Disconnected)
			{
				if (playerInfo->Object.isAlive())
				{
					numTotalAlive++;
					if (std::find(main::Impostors.begin(), main::Impostors.end(), playerInfo->PlayerId) != main::Impostors.end())
					{
						numImpostorsAlive++;
					}
					else if (!playerInfo->Object.isNeutral())
					{
						numCrewAlive++;
					}
				}
			}
		}
		setTeamImpostorsAlive(numImpostorsAlive);
		setTotalAlive(numTotalAlive);
		setCrewAlive(numCrewAlive);
	}
}
