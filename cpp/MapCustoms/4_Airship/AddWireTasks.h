#pragma once

#include <string>
#include <vector>
#include "../../stringhelper.h"

using namespace HarmonyLib;
using namespace UnityEngine;

namespace SuperNewRoles::MapCustoms
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Awake))] class OptimizeMapPatch
	class OptimizeMapPatch
	{
	public:
		static void Postfix(ShipStatus *__instance);
		static void addWireTasks();
	protected:
		static Console *ActivateWiring(const std::wstring &consoleName, int consoleId);
		static Console *ActivateConsole(const std::wstring &objectName);
	};
}
