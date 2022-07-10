#include "Task.h"
#include "main.h"
#include "../../Patch/TaskCount.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Mode::Detective
{

	void Task::TaskCountDetective(GameData *__instance)
	{
		__instance->TotalTasks = 0;
		__instance->CompletedTasks = 0;
		for (int i = 0; i < __instance->AllPlayers->Count; i++)
		{
			try
			{
				GameData::PlayerInfo *playerInfo = __instance->AllPlayers[i];
				if (!playerInfo->Disconnected && playerInfo->Object.isCrew() && (playerInfo->Object.PlayerId != main::DetectivePlayer->PlayerId || !main::IsDetectiveNotTask))
				{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(playerCompleted, playerTotal) = Patch.TaskCount.TaskDate(playerInfo);
					auto [playerCompleted, playerTotal] = Patch::TaskCount::TaskDate(playerInfo);
					__instance->TotalTasks += playerTotal;
					__instance->CompletedTasks += playerCompleted;
				}
			}
			catch (...)
			{

			}
		}
	}
}
