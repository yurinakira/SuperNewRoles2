#pragma once

#include <vector>

using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Doorr
	{
	public:
		static void ResetCoolDown();
		static bool isDoorr(PlayerControl *Player);
		static bool CheckTarget();
		static void DoorrBtn();
	private:
		static float IsPos(Vector3 *mypos, PlainDoor *Door, float distance);
		static PlainDoor *GetDoor();
	public:
		static void EndMeeting();
	};
}
