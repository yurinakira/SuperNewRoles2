#include "Task.h"
#include "../ModeHandler.h"
#include "HASOptions.h"
#include "../../Patch/TaskCount.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Mode::HideAndSeek
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
	void Task::DeadPlayerTaskPatch::Postfix(PlayerControl *__instance, PlayerControl *target)
	{
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}))
		{
			return;
		}
		if (AmongUsClient::Instance->AmHost)
		{
			if (!target->Data->Role.IsImpostor)
			{
				if (ZombieOptions::HASDeathTask->getBool())
				{
					for (PlayerTask *task : *target->myTasks)
					{
						task->Complete();
					}
				}
			}
		}
	}

	void Task::TaskCountHideAndSeek(GameData *__instance)
	{
		__instance->TotalTasks = 0;
		__instance->CompletedTasks = 0;
		for (int i = 0; i < __instance->AllPlayers->Count; i++)
		{
			GameData::PlayerInfo *playerInfo = __instance->AllPlayers[i];
			if (playerInfo->Object.isAlive() && !playerInfo->Object.isImpostor())
			{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(playerCompleted, playerTotal) = SuperNewRoles.Patch.TaskCount.TaskDate(playerInfo);
				auto [playerCompleted, playerTotal] = SuperNewRoles::Patch::TaskCount::TaskDate(playerInfo);
				__instance->TotalTasks += playerTotal;
				__instance->CompletedTasks += playerCompleted;
			}
		}
	}
}
