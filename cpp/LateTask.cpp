#include "LateTask.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles
{

std::vector<LateTask*> LateTask::Tasks;
std::vector<LateTask*> LateTask::AddTasks;

	bool LateTask::run(float deltaTime)
	{
		timer -= deltaTime;
		if (timer <= 0)
		{
			action();
			return true;
		}
		return false;
	}

	LateTask::LateTask(std::function<void()> action, float time, const std::wstring &name)
	{
		this->action = action;
		this->timer = time;
		this->name = name;
		AddTasks.push_back(this);
		//Logger.info("New LateTask \"" + name + "\" is created");
	}

	void LateTask::Update(float deltaTime)
	{
		auto TasksToRemove = std::vector<LateTask*>();
		std::for_each(Tasks.begin(), Tasks.end(), [&] (task)
		{
			//SuperNewRolesPlugin.Logger.LogInfo("LateTask \"" + task.name + "\" Start");
			if (task::run(deltaTime))
			{
				//SuperNewRolesPlugin.Logger.LogInfo("LateTask \"" + task.name + "\" is finished");
				TasksToRemove.push_back(task);
			}
		});
		std::for_each(TasksToRemove.begin(), TasksToRemove.end(), [&] (std::any task)
		{
			return Tasks.Remove(task);
		});
		for (auto task : AddTasks)
		{
			Tasks.push_back(task);
		}
		AddTasks = std::vector<LateTask*>();
	}

	void LateUpdate::Postfix(HudManager *__instance)
	{
		LateTask::Update(Time::deltaTime);
	}
}
