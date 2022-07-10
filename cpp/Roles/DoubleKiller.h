#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class DoubleKiller final
	{
	public:
		static void resetMainCoolDown();
		static void resetSubCoolDown();
		static void EndMeeting();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	public:
		class DoubleKillerFixedPatch
		{
		public:
			static PlayerControl *DoubleKillersetTarget(bool onlyCrewmates = false, bool targetPlayersInVents = false, std::vector<PlayerControl*> &untargetablePlayers = std::vector<PlayerControl>(), PlayerControl *targetingPlayer = nullptr);
		private:
			static void DoubleKillerPlayerOutLineTarget();
		public:
			static void Postfix(PlayerControl *__instance);
		};
	};
}
