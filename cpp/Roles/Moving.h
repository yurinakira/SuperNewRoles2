#pragma once

using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Moving
	{
	public:
		static void ResetCoolDown();
		static bool IsSetPostion();
		static void TP();
		static void SetPostion();
		static bool IsMoving(PlayerControl *Player);
		static void EndMeeting();
	};
}
