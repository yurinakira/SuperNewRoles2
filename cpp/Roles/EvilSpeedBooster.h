#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class EvilSpeedBooster
	{
	public:
		static void ResetCoolDown();
		static void BoostStart();
		static void ResetSpeed();

		static void SpeedBoostCheck();
		static void SpeedBoostEnd();
		static bool IsEvilSpeedBooster(PlayerControl *Player);
		static void EndMeeting();
	};
}
