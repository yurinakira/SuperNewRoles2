#pragma once

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class SelfBomber
	{
	public:
		static void EndMeeting();
		static void ResetCoolDown();
		static bool isSelfBomber(PlayerControl *Player);
		static void SelfBomb();
		static bool GetIsBomb(PlayerControl *source, PlayerControl *player);
	};
}
