#pragma once

using namespace HarmonyLib;

namespace SuperNewRoles
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch] public static class TasksArrow
	class TasksArrow final
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
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(NormalPlayerTask), nameof(NormalPlayerTask.UpdateArrow))] public static class NormalPlayerTaskUpdateArrowPatch
		class NormalPlayerTaskUpdateArrowPatch final
		{
		public:
			static void Postfix(NormalPlayerTask *__instance);
		};

	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AirshipUploadTask), nameof(AirshipUploadTask.UpdateArrow))] public static class AirshipUploadTaskUpdateArrowPatch
		class AirshipUploadTaskUpdateArrowPatch final
		{
		public:
			static void Postfix(AirshipUploadTask *__instance);
		};
	};

	class TasksArrowsOption final
	{
	public:
		static bool hideTaskArrows;

		static void clearAndReloadMapOptions();
	};
}
