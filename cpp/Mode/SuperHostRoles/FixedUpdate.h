#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles::Roles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class FixedUpdate final
	{
	public:
		static std::unordered_map<int, std::wstring> DefaultName;
	private:
		static int UpdateDate;

	private:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.CoShowIntro))] class CoShowIntroPatch
		class CoShowIntroPatch
		{
		public:
			static void Prefix(HudManager *__instance);
		};
	public:
		static std::wstring getDefaultName(PlayerControl *player);
		static void RoleFixedUpdate();
        [HarmonyPatch(typeof(PlayerControl), nameof(PlayerControl.SetKillTimer))]
        public class KilltimerSheriff
        {
            public void Prefix()
            {
                if (ModeHandler.isMode(ModeId.SuperHostRoles) && PlayerControl.LocalPlayer.isRole(CustomRPC.RoleId.Sheriff)) { }
            }
        }*/
		//public static Dictionary<byte, float> UpdateTime;
		static void SetRoleName(PlayerControl *player, bool IsUnchecked = false);

		//短時間で何回も呼ばれると重くなるため更新可能までの時間を指定
	private:
		static constexpr float UpdateDefaultTime = 0.5f;

	public:
		static void SetRoleName(PlayerControl *player, bool commsActive, bool IsUnchecked = false);

		static void SetRoleNames(bool IsUnchecked = false);
		static void Update();
		static void SetDefaultNames();
	};
}
