#pragma once

using namespace UnityEngine;
namespace SuperNewRoles::Patch
{
	class ChatPaste
	{
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyLib.HarmonyPatch(typeof(KeyboardJoystick), nameof(KeyboardJoystick.Update))] class pastepatch
		class pastepatch
		{
		private:
			static void Postfix();
		};
	};
}
