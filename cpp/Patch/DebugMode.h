#pragma once

#include "FixedUpdate.h"
#include "../LateTask.h"
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "../stringhelper.h"

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
	class DebugMode
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(MapConsole), nameof(MapConsole.Use))] public static class MapConsoleUsePatch
		class MapConsoleUsePatch final
		{
		public:
			static void Prefix(MapConsole *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(KeyboardJoystick), nameof(KeyboardJoystick.Update))] public static class DebugManager
		class DebugManager final
		{
		private:
			static System::Random *const random;
			static std::vector<PlayerControl*> bots;
		public:
			class LateTask
			{
			public:
				std::wstring name;
				float timer = 0;
				std::function<void()> action;
				static std::vector<LateTask*> Tasks;
				bool run(float deltaTime);
				LateTask(std::function<void()> action, float time, const std::wstring &name = L"No Name Task");
				static void Update(float deltaTime);
			};
		public:
			static void Postfix(KeyboardJoystick *__instance);

			static std::wstring RandomString(int length);
		};
	public:
		static bool IsDebugMode();
	};
}
