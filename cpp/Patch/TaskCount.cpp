#include "TaskCount.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/Zombie/main.h"
#include "../Mode/Detective/Task.h"
#include "../Mode/HideAndSeek/Task.h"
#include "../Roles/RoleHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Patch
{

	void TaskCount::NormalPlayerTaskPatch::Postfix(NormalPlayerTask *__instance)
	{
		if (__instance->IsComplete && __instance->Arrow == nullptr ? nullptr : __instance->Arrow->isActiveAndEnabled == true)
		{
			if (__instance->Arrow != nullptr)
			{
				if (__instance->Arrow.gameObject != nullptr)
				{
					__instance->Arrow.gameObject.SetActive(false);
				}
			}
		}
			if (__instance->Arrow.gameObject != nullptr)
			{
				__instance->Arrow.gameObject.SetActive(false);
			}
	}

	void TaskCount::AirshipUploadTaskPatch::Postfix(AirshipUploadTask *__instance)
	{
		if (__instance->IsComplete)
		{
			if (__instance->Arrows != nullptr)
			{
				__instance->Arrows.DoIf([&] (std::any x)
				{
					return x != nullptr && x::isActiveAndEnabled;
				}, [&] (std::any x)
				{
					if (x::gameObject != nullptr)
					{
						x::gameObject::SetActive(false);
					}
				});
			}
		}
			__instance->Arrows.DoIf([&] (std::any x)
			{
				return x != nullptr && x::isActiveAndEnabled;
			}, [&] (std::any x)
			{
				if (x::gameObject != nullptr)
				{
					x::gameObject::SetActive(false);
				}
			});
	}

	std::tuple<int, int> TaskCount::TaskDateNoClearCheck(GameData::PlayerInfo *playerInfo)
	{
		int TotalTasks = 0;
		int CompletedTasks = 0;

		for (int j = 0; j < playerInfo->Tasks->Count; j++)
		{
			TotalTasks++;
			if (playerInfo->Tasks[j].Complete)
			{
				CompletedTasks++;
			}
		}
		return std::make_tuple(CompletedTasks, TotalTasks);
	}

	std::tuple<int, int> TaskCount::TaskDate(GameData::PlayerInfo *playerInfo)
	{
		int TotalTasks = 0;
		int CompletedTasks = 0;
		if (!playerInfo->Disconnected && playerInfo->Tasks != nullptr && playerInfo->Object && (PlayerControl::GameOptions::GhostsDoTasks || !playerInfo->IsDead) && playerInfo->Role && playerInfo->Role.TasksCountTowardProgress)
		{
			for (int j = 0; j < playerInfo->Tasks->Count; j++)
			{
				TotalTasks++;
				if (playerInfo->Tasks[j].Complete)
				{
					CompletedTasks++;
				}
			}
		}
		return std::make_tuple(CompletedTasks, TotalTasks);
	}

	void TaskCount::GameDataRecomputeTaskCountsPatch::Postfix(GameData *__instance)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		switch (ModeHandler::GetMode())
		{
			case ModeId::SuperHostRoles:
			case ModeId::Default:
				CountDefaultTask(__instance);
				return;
			case ModeId::Zombie:
				Mode::Zombie::main::CountTaskZombie(__instance);
				return;
			case ModeId::Detective:
				Mode::Detective::Task::TaskCountDetective(__instance);
				return;
			case ModeId::HideAndSeek:
				Mode::HideAndSeek::Task::TaskCountHideAndSeek(__instance);
				return;
		}
	}

	void TaskCount::CountDefaultTask(GameData *__instance)
	{
		__instance->TotalTasks = 0;
		__instance->CompletedTasks = 0;
		for (int i = 0; i < __instance->AllPlayers->Count; i++)
		{
			GameData::PlayerInfo *playerInfo = __instance->AllPlayers[i];
			if (!RoleHelpers::isClearTask(playerInfo->Object) && playerInfo->Object.IsPlayer())
			{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(playerCompleted, playerTotal) = TaskCount.TaskDate(playerInfo);
				auto [playerCompleted, playerTotal] = TaskCount::TaskDate(playerInfo);
				__instance->TotalTasks += playerTotal;
				__instance->CompletedTasks += playerCompleted;
			}
		}
	}
}
