#include "SetTarget.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "RoleClass.h"
#include "../Patch/PlayerControlPatch.h"

using namespace SuperNewRoles::Patches;

namespace SuperNewRoles::Roles
{

	void SetTarget::ImpostorSetTarget()
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Kunoichi))
		{
			FastDestroyableSingleton<HudManager*>::getInstance().KillButton::SetTarget(PlayerControl::LocalPlayer);
			return;
		}
		std::vector<PlayerControl*> untarget;
		untarget.insert(untarget.end(), RoleClass::SideKiller::MadKillerPlayer.begin(), RoleClass::SideKiller::MadKillerPlayer.end());
		untarget.insert(untarget.end(), RoleClass::Spy::SpyPlayer.begin(), RoleClass::Spy::SpyPlayer.end());
		FastDestroyableSingleton<HudManager*>::getInstance().KillButton::SetTarget(PlayerControlFixedUpdatePatch::setTarget(true, false, untarget, nullptr));
	}
}
