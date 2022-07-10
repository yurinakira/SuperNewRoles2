#include "Lighter.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"

using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{

	void Lighter::ResetCoolDown()
	{
		HudManagerStartPatch::LighterLightOnButton->MaxTimer = RoleClass::Lighter::CoolTime;
		RoleClass::Lighter::ButtonTimer = DateTime::Now;
	}

	bool Lighter::isLighter(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Lighter::LighterPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Lighter::LightOnStart()
	{
		RoleClass::Lighter::IsLightOn = true;
	}

	void Lighter::LightOutEnd()
	{
		if (!RoleClass::Lighter::IsLightOn)
		{
			return;
		}
		RoleClass::Lighter::IsLightOn = false;
	}

	void Lighter::EndMeeting()
	{
		HudManagerStartPatch::LighterLightOnButton->MaxTimer = RoleClass::Lighter::CoolTime;
		RoleClass::Lighter::ButtonTimer = DateTime::Now;
		RoleClass::Lighter::IsLightOn = false;
	}
}
