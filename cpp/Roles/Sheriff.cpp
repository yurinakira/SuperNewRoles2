#include "Sheriff.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "CountChanger.h"
#include "TeamRoleType.h"
#include "RoleHelper.h"

using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{

	void Sheriff::ResetKillCoolDown()
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::RemoteSheriff))
		{
			HudManagerStartPatch::SheriffKillButton->MaxTimer = RoleClass::RemoteSheriff::CoolTime;
			HudManagerStartPatch::SheriffKillButton->Timer = RoleClass::RemoteSheriff::CoolTime;
			RoleClass::Sheriff::ButtonTimer = DateTime::Now;
		}
		else
		{
			if (std::find(RoleClass::Chief::SheriffPlayer.begin(), RoleClass::Chief::SheriffPlayer.end(), CachedPlayer::LocalPlayer->PlayerId) != RoleClass::Chief::SheriffPlayer.end())
			{
				HudManagerStartPatch::SheriffKillButton->MaxTimer = RoleClass::Chief::CoolTime;
			}
			else
			{
				HudManagerStartPatch::SheriffKillButton->MaxTimer = RoleClass::Sheriff::CoolTime;
			}
			HudManagerStartPatch::SheriffKillButton->Timer = HudManagerStartPatch::SheriffKillButton->MaxTimer;
		}
	}

	bool Sheriff::IsSheriffKill(PlayerControl *Target)
	{
		auto roledata = CountChanger::GetRoleType(Target);
		if (roledata == TeamRoleType::Impostor)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isMadRole(Target) && RoleClass::Sheriff::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isFriendRole(Target) && RoleClass::Sheriff::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isNeutral(Target) && RoleClass::Sheriff::IsNeutralKill)
		{
			return true;
		}
		if (RoleClass::Sheriff::IsLoversKill && SuperNewRoles::RoleHelpers::IsLovers(Target))
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isRole(Target, CustomRPC::RoleId::HauntedWolf))
		{
			return true;
		}
		return false;
	}

	bool Sheriff::IsChiefSheriffKill(PlayerControl *Target)
	{
		auto roledata = CountChanger::GetRoleType(Target);
		if (roledata == TeamRoleType::Impostor)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isMadRole(Target) && RoleClass::Chief::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isFriendRole(Target) && RoleClass::Chief::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isNeutral(Target) && RoleClass::Chief::IsNeutralKill)
		{
			return true;
		}
		if (RoleClass::Chief::IsLoversKill && SuperNewRoles::RoleHelpers::IsLovers(Target))
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isRole(Target, CustomRPC::RoleId::HauntedWolf))
		{
			return true;
		}
		return false;
	}

	bool Sheriff::IsRemoteSheriffKill(PlayerControl *Target)
	{
		auto roledata = CountChanger::GetRoleType(Target);
		if (roledata == TeamRoleType::Impostor)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isMadRole(Target) && RoleClass::RemoteSheriff::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isFriendRole(Target) && RoleClass::RemoteSheriff::IsMadRoleKill)
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isNeutral(Target) && RoleClass::RemoteSheriff::IsNeutralKill)
		{
			return true;
		}
		if (RoleClass::RemoteSheriff::IsLoversKill && SuperNewRoles::RoleHelpers::IsLovers(Target))
		{
			return true;
		}
		if (SuperNewRoles::RoleHelpers::isRole(Target, CustomRPC::RoleId::HauntedWolf))
		{
			return true;
		}
		return false;
	}

	bool Sheriff::IsSheriff(PlayerControl *Player)
	{
		if (SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::Sheriff) || SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::RemoteSheriff))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Sheriff::IsSheriffButton(PlayerControl *Player)
	{
		if (SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::Sheriff))
		{
			if (RoleClass::Sheriff::KillMaxCount > 0)
			{
				return true;
			}
		}
		else if (SuperNewRoles::RoleHelpers::isRole(Player, CustomRPC::RoleId::RemoteSheriff))
		{
			if (RoleClass::RemoteSheriff::KillMaxCount > 0)
			{
				return true;
			}
		}
		return false;
	}

	void Sheriff::EndMeeting()
	{
		ResetKillCoolDown();
	}
}
