#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Smasher final
	{
	public:
		static void resetCoolDown();
		static void resetSmashCoolDown();
		static void EndMeeting();
		static void setPlayerOutline(PlayerControl *target, Color *color);
	};
}
