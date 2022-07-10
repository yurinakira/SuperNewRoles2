#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <vector>
#include <stdexcept>
#include <functional>
#include "../stringhelper.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles
{
	class RoleHelpers final
	{
	public:
		static bool isCrew(PlayerControl *player);

		static bool isImpostor(PlayerControl *player);

		static bool isHauntedWolf(PlayerControl *player);

		//We are Mad!
		static bool isMadRole(PlayerControl *player);

		//We are JackalFriends!
		static bool isFriendRole(PlayerControl *player);

		static bool IsQuarreled(PlayerControl *player, bool IsChache = true);
		static bool IsLovers(PlayerControl *player, bool IsChache = true);
		static void SetQuarreled(PlayerControl *player1, PlayerControl *player2);
		static void SetQuarreledRPC(PlayerControl *player1, PlayerControl *player2);
		static void SetLovers(PlayerControl *player1, PlayerControl *player2);
		static void SetLoversRPC(PlayerControl *player1, PlayerControl *player2);
		static void RemoveQuarreled(PlayerControl *player);
		static PlayerControl *GetOneSideQuarreled(PlayerControl *player, bool IsChache = true);
		static PlayerControl *GetOneSideLovers(PlayerControl *player, bool IsChache = true);
		static bool IsJackalTeam(PlayerControl *player);
		static bool IsJackalTeamJackal(PlayerControl *player);
		static bool IsJackalTeamSidekick(PlayerControl *player);

		static void ShowFlash(Color *color, float duration = 1.0f);

		static void setRole(PlayerControl *player, RoleId role);
	private:
		static PlayerControl *ClearTarget;
	public:
		static void ClearRole(PlayerControl *player);
		static void setRoleRPC(PlayerControl *Player, RoleId SelectRoleDate);
		static bool isClearTask(PlayerControl *player);
		static bool IsUseVent(PlayerControl *player);
		static bool IsSabotage();
		static bool IsComms();
		static bool IsUseSabo(PlayerControl *player);
		static bool IsImpostorLight(PlayerControl *player);
		static bool isNeutral(PlayerControl *player);
		static bool isRole(PlayerControl *p, RoleId role, bool IsChache = true);
		static bool isRole(PlayerControl *p, std::vector<RoleId> &roles);
		static float getCoolTime(PlayerControl *__instance);
		static float GetEndMeetingKillCoolTime(PlayerControl *p);
		static RoleId getGhostRole(PlayerControl *player, bool IsChache = true);
		static bool isGhostRole(RoleId role);
		static bool isGhostRole(PlayerControl *p, RoleId role, bool IsChache = true);
		static RoleId getRole(PlayerControl *player, bool IsChache = true);
		static bool isDead(PlayerControl *player);
		static bool isAlive(PlayerControl *player);
	};
}
