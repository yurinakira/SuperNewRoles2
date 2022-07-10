#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles
{
	//TownOfHostより！！
	class LateTask
	{
	public:
		std::wstring name;
		float timer = 0;
		std::function<void()> action;
		static std::vector<LateTask*> Tasks;
		static std::vector<LateTask*> AddTasks;
		bool run(float deltaTime);
		LateTask(std::function<void()> action, float time, const std::wstring &name = L"No Name Task");
		static void Update(float deltaTime);
	};
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] class LateUpdate
	class LateUpdate
	{
	public:
		static void Postfix(HudManager *__instance);
	};
}
