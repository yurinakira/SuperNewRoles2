#pragma once

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class SecretlyKiller final
	{
	public:
		static void EndMeeting();
		//リセクール (by:Buttons.cs)
		static void MainResetCoolDown();
		static void SecretlyResetCoolDown();
		static void AllResetCoolDown();

		//シークレットキル (by:Buttons.cs)
		static void SecretlyKill();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	};
}
