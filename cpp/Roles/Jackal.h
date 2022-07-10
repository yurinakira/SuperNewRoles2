#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Jackal
	{
	public:
		static void resetCoolDown();
		static void EndMeeting();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	public:
		class JackalFixedPatch
		{
		public:
			static PlayerControl *JackalsetTarget(bool onlyCrewmates = false, bool targetPlayersInVents = false, std::vector<PlayerControl*> &untargetablePlayers = std::vector<PlayerControl>(), PlayerControl *targetingPlayer = nullptr);
		private:
			static void JackalPlayerOutLineTarget();
		public:
			static void Postfix(PlayerControl *__instance, RoleId role);
		};
	};
}
