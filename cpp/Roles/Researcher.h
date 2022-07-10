#pragma once

using namespace HarmonyLib;

namespace SuperNewRoles::Roles
{
	class Researcher
	{
	public:
		static bool IsTarget();
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(UseButton), nameof(UseButton.DoClick))] class UseButtonUsePatch
		class UseButtonUsePatch
		{
		private:
			static void Postfix(UseButton *__instance);
		};
	public:
		class ReseUseButtonSetTargetPatch
		{
		public:
			static void Postfix(PlayerControl *__instance);
		};
	};
}
