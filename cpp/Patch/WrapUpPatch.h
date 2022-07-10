#pragma once

#include <vector>
#include <limits>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;

namespace SuperNewRoles::Patch
{
	class WrapUpPatch
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ExileController), nameof(ExileController.WrapUp))] public class ExileControllerWrapUpPatch
		class ExileControllerWrapUpPatch
		{
		public:
			static void Prefix(ExileController *__instance);
			static void Postfix(ExileController *__instance);
		};
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(AirshipExileController), nameof(AirshipExileController.WrapUpAndSpawn))] public class AirshipExileControllerWrapUpPatch
		class AirshipExileControllerWrapUpPatch
		{
		public:
			static void Prefix(AirshipExileController *__instance);
			static void Postfix(AirshipExileController *__instance);
		};
	public:
		static void Prefix(GameData::PlayerInfo *exiled);
		static void Postfix(GameData::PlayerInfo *exiled);
	};
}
