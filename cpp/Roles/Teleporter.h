#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class Teleporter
	{
	public:
		static void ResetCoolDown();
		static void TeleportStart();
		static bool IsTeleporter(PlayerControl *Player);
		static void EndMeeting();
	};
}
