#pragma once

using namespace HarmonyLib;

namespace SuperNewRoles::Patch
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(SplashManager), nameof(SplashManager.Update))] class SplashLogoAnimatorPatch
	class SplashLogoAnimatorPatch
	{
	public:
		static void Prefix(SplashManager *__instance);
	};
}
