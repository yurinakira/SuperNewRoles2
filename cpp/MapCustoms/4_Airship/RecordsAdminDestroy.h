#pragma once

using namespace HarmonyLib;
using namespace UnityEngine;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::MapCustoms
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ShipStatus),nameof(ShipStatus.Awake))] public class RecordsAdminDestroy
	class RecordsAdminDestroy
	{
	public:
		static void Postfix();
	};
}
