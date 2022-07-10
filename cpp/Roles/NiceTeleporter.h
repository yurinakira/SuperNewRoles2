#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class NiceTeleporter
	{
	public:
		static void ResetCoolDown();
		static void TeleportStart();
		static bool IsNiceTeleporter(PlayerControl *Player);
		static void EndMeeting();
	};
}
