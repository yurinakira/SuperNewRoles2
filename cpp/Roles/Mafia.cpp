#include "Mafia.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../BotManager.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	bool Mafia::IsKillFlag()
	{
		if (RoleClass::Mafia::CachedIs)
		{
			return true;
		}
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::BotManager::IsPlayer(player->PlayerControl) && SuperNewRoles::RoleHelpers::isAlive(player->PlayerControl) && SuperNewRoles::RoleHelpers::isImpostor(player->PlayerControl) && !SuperNewRoles::RoleHelpers::isRole(player->PlayerControl, RoleId::Mafia) && !SuperNewRoles::RoleHelpers::isRole(player->PlayerControl, RoleId::Egoist))
			{
				return false;
			}
		}
		RoleClass::Mafia::CachedIs = true;
		return true;
	}

	void Mafia::FixedUpdate()
	{
		if (IsKillFlag())
		{
			if (!RoleClass::IsMeeting)
			{
				if (!HudManager::Instance->KillButton.isActiveAndEnabled)
				{
					HudManager::Instance->KillButton.Show();
				}
			}
		}
		else
		{
			if (HudManager::Instance->KillButton.isActiveAndEnabled)
			{
				HudManager::Instance->KillButton->Hide();
			}

			if (!RoleClass::IsMeeting)
			{
				PlayerControl::LocalPlayer::SetKillTimer(PlayerControl::LocalPlayer::killTimer - Time::fixedDeltaTime);
			}
		}
	}
}
