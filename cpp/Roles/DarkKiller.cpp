#include "DarkKiller.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/MapUtilities.h"

namespace SuperNewRoles::Roles
{

	void DarkKiller::MurderPatch::Postfix(PlayerControl *__instance)
	{
		if (CachedPlayer::LocalPlayer->PlayerId == __instance->PlayerId && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::DarkKiller))
		{
			PlayerControl::LocalPlayer::SetKillTimerUnchecked(RoleClass::DarkKiller::KillCoolTime);
		}
	}

	void DarkKiller::SetDarkKillerButton()
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::DarkKiller))
		{
			if (!RoleClass::DarkKiller::KillButtonDisable)
			{
				FastDestroyableSingleton<HudManager*>::getInstance().KillButton->enabled = true;

				auto ma = MapUtilities::CachedShipStatus->Systems[SystemTypes::Electrical].CastFast<SwitchSystem*>();
				if (ma != nullptr && !ma->IsActive)
				{
					FastDestroyableSingleton<HudManager*>::getInstance().KillButton->enabled = false;
				}
			}
		}
	}

	void DarkKiller::FixedUpdate::Postfix()
	{
		SetDarkKillerButton();
	}
}
