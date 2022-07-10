#pragma once

#include <tuple>

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Patch
{
	class TaskCount
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(NormalPlayerTask), nameof(NormalPlayerTask.FixedUpdate))] public static class NormalPlayerTaskPatch
		class NormalPlayerTaskPatch final
		{
		public:
			static void Postfix(NormalPlayerTask *__instance);
		};

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AirshipUploadTask), nameof(AirshipUploadTask.FixedUpdate))] public static class AirshipUploadTaskPatch
		class AirshipUploadTaskPatch final
		{
		public:
			static void Postfix(AirshipUploadTask *__instance);
		};
	public:
		static std::tuple<int, int> TaskDateNoClearCheck(GameData::PlayerInfo *playerInfo);
		static std::tuple<int, int> TaskDate(GameData::PlayerInfo *playerInfo);

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(GameData), nameof(GameData.RecomputeTaskCounts))] private static class GameDataRecomputeTaskCountsPatch
		class GameDataRecomputeTaskCountsPatch final
		{
		public:
			static void Postfix(GameData *__instance);
		};
	private:
		static void CountDefaultTask(GameData *__instance);
	};
}
