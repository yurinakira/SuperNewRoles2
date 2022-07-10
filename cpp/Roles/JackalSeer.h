#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class JackalSeer
	{
	public:
		static void resetCoolDown();
		static void EndMeeting();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	public:
		class JackalSeerFixedPatch
		{
		public:
			static PlayerControl *JackalSeersetTarget(bool onlyCrewmates = false, bool targetPlayersInVents = false, std::vector<PlayerControl*> &untargetablePlayers = std::vector<PlayerControl>(), PlayerControl *targetingPlayer = nullptr);
		private:
			static void JackalSeerPlayerOutLineTarget();
		public:
			static void Postfix(PlayerControl *__instance, RoleId role);
		};
	};
}
