#pragma once

#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ExileController), nameof(ExileController.Begin))] public class Bakery
	class Bakery
	{
	private:
		static TMPro::TextMeshPro *breadText;
	public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ExileController __instance, [HarmonyArgument(0)] GameData.PlayerInfo exiled, [HarmonyArgument(1)] bool tie)
		static bool Prefix(ExileController *__instance, GameData::PlayerInfo *exiled, bool tie);
		//生存判定
		static bool BakeryAlive();
		static std::wstring GetExileText();

	private:
		static void Postfix(ExileController *__instance);

		//会議終了
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ExileController), nameof(ExileController.ReEnableGameplay))] public class BakeryChatDisable
		class BakeryChatDisable
		{
		private:
			static void Postfix(ExileController *__instance);
		};
	};
}
