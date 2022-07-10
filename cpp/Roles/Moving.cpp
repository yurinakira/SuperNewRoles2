#include "Moving.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"

using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Moving::ResetCoolDown()
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::EvilMoving))
		{
			HudManagerStartPatch::MovingTpButton->MaxTimer = RoleClass::EvilMoving::CoolTime;
		}
		else
		{
			HudManagerStartPatch::MovingTpButton->MaxTimer = RoleClass::Moving::CoolTime;
		}
		RoleClass::Moving::ButtonTimer = DateTime::Now;
	}

	bool Moving::IsSetPostion()
	{
		Vector3 tempVar(0, 0, 0);
		if (!(RoleClass::Moving::setpostion == &tempVar))
		{
			return true;
		}
		return false;
	}

	void Moving::TP()
	{
		CachedPlayer::LocalPlayer->transform->position = RoleClass::Moving::setpostion;
	}

	void Moving::SetPostion()
	{
		RoleClass::Moving::setpostion = CachedPlayer::LocalPlayer->transform->position;
	}

	bool Moving::IsMoving(PlayerControl *Player)
	{
		if (SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::Moving) || SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::EvilMoving))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Moving::EndMeeting()
	{
		HudManagerStartPatch::MovingSetButton->Timer = 0.0f;
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::EvilMoving))
		{
			HudManagerStartPatch::MovingTpButton->MaxTimer = RoleClass::EvilMoving::CoolTime;
		}
		else
		{
			HudManagerStartPatch::MovingTpButton->MaxTimer = RoleClass::Moving::CoolTime;
		}
		RoleClass::Moving::ButtonTimer = DateTime::Now;
	}
}
