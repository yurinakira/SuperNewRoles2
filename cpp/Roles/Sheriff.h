#pragma once

#include <algorithm>

using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class Sheriff
	{
	public:
		static void ResetKillCoolDown();
		static bool IsSheriffKill(PlayerControl *Target);
		static bool IsChiefSheriffKill(PlayerControl *Target);
		static bool IsRemoteSheriffKill(PlayerControl *Target);
		static bool IsSheriff(PlayerControl *Player);
		static bool IsSheriffButton(PlayerControl *Player);
		static void EndMeeting();
	};
}
