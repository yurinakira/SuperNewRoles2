#pragma once

#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles::Patch
{
	class Chat
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(ChatBubble), nameof(ChatBubble.SetName))] public static class SetBubbleName
		class SetBubbleName final
		{
		public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(ChatBubble __instance, [HarmonyArgument(0)] string playerName)
			static void Postfix(ChatBubble *__instance, const std::wstring &playerName);
		};
	};
}
