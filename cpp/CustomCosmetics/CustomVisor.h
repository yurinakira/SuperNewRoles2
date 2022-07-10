#pragma once

#include <vector>
#include <stdexcept>

using namespace BepInEx;
using namespace BepInEx::Configuration;
using namespace BepInEx::IL2CPP;
using namespace HarmonyLib;
using namespace Hazel;
using namespace UnhollowerBaseLib;
using namespace UnityEngine;

namespace SuperNewRoles::CustomCosmetics
{
	class CustomVisor
	{
	public:
		static bool isAdded;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HatManager), nameof(HatManager.GetVisorById))] class UnlockedVisorPatch
		class UnlockedVisorPatch
		{
		public:
			static void Postfix(HatManager *__instance);
		};
	};
}
