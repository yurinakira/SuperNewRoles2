#include "Patch.h"
#include "../SabotageManager.h"
#include "main.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Sabotage::CognitiveDeficit
{

ProgressTracker *TaskBar::Instance;

	void TaskBar::TaskBarPatch::Postfix(ProgressTracker *__instance)
	{
		Instance = __instance;
		if (PlayerControl::GameOptions::TaskBarMode != TaskBarMode::Invisible)
		{
			if (SabotageManager::thisSabotage == SabotageManager::CustomSabotage::CognitiveDeficit)
			{
				__instance->gameObject.SetActive(main::IsLocalEnd);
			}
		}
	}
}
