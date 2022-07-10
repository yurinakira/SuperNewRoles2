#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{
	class Clergyman
	{
	public:
		static void ResetCoolDown();
		static bool isClergyman(PlayerControl *Player);
		static void LightOutStart();
		static bool IsLightOutVision();
		static bool IsLightOutVisionNoTime();
		static void LightOutStartRPC();
		static void EndMeeting();
	};
}
