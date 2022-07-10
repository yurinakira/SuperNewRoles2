#pragma once

#include <string>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{
	class FixedUpdate
	{
		/*
		[HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.SetSkin))]
		class Setcolorskin
		{
		    public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] ref string skinid)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo(__instance.nameText().text + ":" + skinid);
		    }
		}
		[HarmonyPatch(typeof(PlayerControl),nameof(PlayerControl.SetColor))]
		class Setcolor
		{
		    public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] ref int colorid)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo(__instance.nameText().text+":"+colorid);
		    }
		}
		[HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.SetHat))]
		class Sethat
		{
		    public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] ref string colorid)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo("[SetHat]"+__instance.nameText().text + ":" + colorid);
		    }
		}
		[HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.SetVisor))]
		class Setvisor
		{
		    public static void Postfix(PlayerControl __instance, [HarmonyArgument(0)] ref string colorid)
		    {
		        SuperNewRolesPlugin.Logger.LogInfo("[SetVisor]" + __instance.nameText().text + ":" + colorid);
		    }
		}
		*/
	public:
		static float NameChangeTimer;
		static bool IsStart;
	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] class TimerUpdate
		class TimerUpdate
		{
		public:
			static void Postfix(HudManager *__instance);
		};
	public:
		static int FixedUpdateTimer;
		static void Update();
	};
}
