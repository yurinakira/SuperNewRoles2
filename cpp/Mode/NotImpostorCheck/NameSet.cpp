#include "NameSet.h"
#include "../../Helpers/CachedPlayer.h"
#include "main.h"
#include "../SuperHostRoles/main.h"
#include "../../Roles/RoleHelper.h"
#include "../../ModHelpers.h"

using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::NotImpostorCheck
{

	void NameSet::Postfix()
	{
		int LocalId = CachedPlayer::LocalPlayer->PlayerId;
		if (std::find(main::Impostors.begin(), main::Impostors.end(), LocalId) != main::Impostors.end())
		{
			for (auto p : CachedPlayer::AllPlayers)
			{
				if (SuperNewRoles::RoleHelpers::isAlive(p) && p->PlayerId != LocalId)
				{
					SuperNewRoles::ModHelpers::nameText(p)->color = Color::white;
				}
			}
		}
	}
}
