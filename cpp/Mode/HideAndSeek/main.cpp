#include "main.h"
#include "../../Main.h"

using namespace SuperNewRoles::EndGame;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{

	bool main::EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (statistics->CrewAlive == 0)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[HAS]ENDDED!!!");
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::ImpostorByKill, false);
			return true;
		}
		else if (GameData::Instance->TotalTasks > 0 && GameData::Instance->TotalTasks <= GameData::Instance->CompletedTasks)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[HAS]TASKEND!");
			__instance->enabled = false;
			ShipStatus::RpcEndGame(GameOverReason::HumansByTask, false);
			return true;
		}
		else
		{
			return false;
		}
	}

	void main::ClearAndReload()
	{
	}
}
