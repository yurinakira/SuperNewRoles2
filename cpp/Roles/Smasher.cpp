#include "Smasher.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Smasher::resetCoolDown()
	{
		HudManagerStartPatch::DoubleKillerMainKillButton->MaxTimer = RoleClass::Smasher::KillCoolTime;
		HudManagerStartPatch::DoubleKillerMainKillButton->Timer = RoleClass::Smasher::KillCoolTime;
	}

	void Smasher::resetSmashCoolDown()
	{
		HudManagerStartPatch::DoubleKillerSubKillButton->MaxTimer = 0.1f;
		HudManagerStartPatch::DoubleKillerSubKillButton->Timer = 0.1f;
	}

	void Smasher::EndMeeting()
	{
		resetCoolDown();
		resetSmashCoolDown();
		HudManagerStartPatch::DoubleKillerSubKillButton->MaxTimer = 0.1f;
	}

	void Smasher::setPlayerOutline(PlayerControl *target, Color *color)
	{
		if (target == nullptr || target->MyRend == nullptr)
		{
			return;
		}

		SuperNewRoles::ModHelpers::MyRend(target)->material.SetFloat(L"_Outline", 1.0f);
		SuperNewRoles::ModHelpers::MyRend(target)->material.SetColor(L"_OutlineColor", color);
	}
}
