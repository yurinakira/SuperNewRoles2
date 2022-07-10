#include "TasksArrows.h"
#include "Config.h"

using namespace HarmonyLib;

namespace SuperNewRoles
{

	void TasksArrow::NormalPlayerTaskPatch::Postfix(NormalPlayerTask *__instance)
	{
		bool showArrows = !TasksArrowsOption::hideTaskArrows && !__instance->IsComplete && __instance->TaskStep > 0;
		if (__instance->Arrow != nullptr)
		{
			if (__instance->Arrow.gameObject != nullptr)
			{
				__instance->Arrow.gameObject.SetActive(showArrows);
			}
		}
		{
		if (__instance->Arrow.gameObject != nullptr)
		{
			__instance->Arrow.gameObject.SetActive(showArrows);
		}
	}
	}

	void TasksArrow::AirshipUploadTaskPatch::Postfix(AirshipUploadTask *__instance)
	{
		bool showArrows = !TasksArrowsOption::hideTaskArrows && !__instance->IsComplete && __instance->TaskStep > 0;
		if (__instance->Arrows != nullptr)
		{
			__instance->Arrows.DoIf([&] (std::any x)
			{
				return x != nullptr;
			}, [&] (std::any x)
			{
				if (x::gameObject != nullptr)
				{
					x::gameObject::SetActive(showArrows);
				}
			});
		}
		__instance->Arrows.DoIf([&] (std::any x)
		{
			return x != nullptr;
		}, [&] (std::any x)
		{
			if (x::gameObject != nullptr)
			{
				x::gameObject::SetActive(showArrows);
			}
		});
	}

	void TasksArrow::NormalPlayerTaskUpdateArrowPatch::Postfix(NormalPlayerTask *__instance)
	{
		if (TasksArrowsOption::hideTaskArrows)
		{
			if (__instance->Arrow != nullptr)
			{
				if (__instance->Arrow.gameObject != nullptr)
				{
					__instance->Arrow.gameObject.SetActive(false);
				}
			}
			{
			if (__instance->Arrow.gameObject != nullptr)
			{
				__instance->Arrow.gameObject.SetActive(false);
			}
		}
		}
	}

	void TasksArrow::AirshipUploadTaskUpdateArrowPatch::Postfix(AirshipUploadTask *__instance)
	{
		if (TasksArrowsOption::hideTaskArrows)
		{
			if (__instance->Arrows != nullptr)
			{
				__instance->Arrows.DoIf([&] (std::any x)
				{
					return x != nullptr;
				}, [&] (std::any x)
				{
					if (x::gameObject != nullptr)
					{
						x::gameObject::SetActive(false);
					}
				});
			}
			__instance->Arrows.DoIf([&] (std::any x)
			{
				return x != nullptr;
			}, [&] (std::any x)
			{
				if (x::gameObject != nullptr)
				{
					x::gameObject::SetActive(false);
				}
			});
		}
	}

bool TasksArrowsOption::hideTaskArrows = false;

	void TasksArrowsOption::clearAndReloadMapOptions()
	{
		hideTaskArrows = ConfigRoles::getHideTaskArrows()->Value;
	}
}
