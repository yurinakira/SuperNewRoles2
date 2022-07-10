#pragma once

#include <vector>
#include <stdexcept>

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class Demon final
	{
	public:
		static void DemonCurse(PlayerControl *target, PlayerControl *source = nullptr);

		static std::vector<PlayerControl*> GetCurseData(PlayerControl *player);

		static std::vector<PlayerControl*> GetUntarget();

		static bool IsCursed(PlayerControl *source, PlayerControl *target);

		static std::vector<PlayerControl*> GetIconPlayers(PlayerControl *player = nullptr);
		static bool IsViewIcon(PlayerControl *player);

		static bool IsButton();

		static bool IsWin(PlayerControl *Demon);

		static bool IsDemonWinFlag();
	};
}
