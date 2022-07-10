#pragma once

using namespace HarmonyLib;

//参考=>https://github.com/Koke1024/Town-Of-Moss/blob/main/TownOfMoss/Patches/MeltDownBoost.cs

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ReactorSystemType), nameof(ReactorSystemType.Detoriorate))] public static class MeltdownBooster
	class MeltdownBooster final
	{
	public:
		static void Prefix(ReactorSystemType *__instance, float deltaTime);
	};

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HeliSabotageSystem), nameof(HeliSabotageSystem.Detoriorate))] public static class HeliMeltdownBooster
	class HeliMeltdownBooster final
	{
	public:
		static void Prefix(HeliSabotageSystem *__instance, float deltaTime);
	};
}
