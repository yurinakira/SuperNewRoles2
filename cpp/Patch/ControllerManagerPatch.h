#pragma once

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ControllerManager), nameof(ControllerManager.Update))] class ControllerManagerUpdatePatch
	class ControllerManagerUpdatePatch
	{
		static (int, int)[] resolutions = {(480, 270), (640, 360), (800, 450), (1280, 720), (1600, 900)};
	private:
		static int resolutionIndex;
	public:
		static void Postfix(ControllerManager *__instance);
	};
}
