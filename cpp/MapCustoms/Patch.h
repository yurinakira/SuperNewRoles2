#pragma once

using namespace HarmonyLib;
using namespace static PlayerControl;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{
	class Patch
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus), nameof(ShipStatus.Awake))] static class ShipStatus_AwakePatch
		class ShipStatus_AwakePatch final
		{
		private:
			static void Postfix(ShipStatus *__instance);
		};
	};
}
