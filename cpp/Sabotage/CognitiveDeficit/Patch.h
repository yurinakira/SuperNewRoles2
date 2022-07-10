#pragma once

using namespace HarmonyLib;

namespace SuperNewRoles::Sabotage::CognitiveDeficit
{
	class TaskBar final
	{
	public:
		static ProgressTracker *Instance;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ProgressTracker), nameof(ProgressTracker.FixedUpdate))] class TaskBarPatch
		class TaskBarPatch
		{
		public:
			static void Postfix(ProgressTracker *__instance);
		};
	};
}
