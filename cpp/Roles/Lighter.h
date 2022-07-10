#pragma once

using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class Lighter
	{
	public:
		static void ResetCoolDown();
		static bool isLighter(PlayerControl *Player);
		static void LightOnStart();
		static void LightOutEnd();
		static void EndMeeting();
	};
}
