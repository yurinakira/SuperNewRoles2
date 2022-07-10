#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class TeleportingJackal
	{
	public:
		static void resetCoolDown();
		static void EndMeeting();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	public:
		class JackalFixedPatch
		{
		public:
			static PlayerControl *TeleportingJackalsetTarget(bool onlyCrewmates = false, bool targetPlayersInVents = false, std::vector<PlayerControl*> &untargetablePlayers = std::vector<PlayerControl>(), PlayerControl *targetingPlayer = nullptr);
		private:
			static void TeleportingJackalPlayerOutLineTarget();
		public:
			static void Postfix(PlayerControl *__instance);
		};
	public:
		static void ResetCoolDown();
		static void TeleportStart();
		static bool IsTeleportingJackal(PlayerControl *Player);
	};
}
