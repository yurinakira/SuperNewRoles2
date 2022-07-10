#include "Pursuer.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"
#include "../Main.h"
#include "../ModHelpers.h"
#include "RoleClass.h"

using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Pursuer::PursureUpdate::Postfix()
	{
		float min_target_distance = std::numeric_limits<float>::max();
		PlayerControl *target = nullptr;

		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p->PlayerControl) && !SuperNewRoles::RoleHelpers::isImpostor(p->PlayerControl))
			{
				float target_distance = Vector3::Distance(CachedPlayer::LocalPlayer->transform->position, p->transform->position);

				if (target_distance < min_target_distance)
				{
					min_target_distance = target_distance;
					target = p;
				}
			}
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[Pursuer]Target:" + target == nullptr ? nullptr : SuperNewRoles::ModHelpers::nameText(target)->text);
		if (target != nullptr)
		{
			try
			{
				RoleClass::Pursuer::arrow->Update(target->transform.position, RoleClass::Pursuer::color);
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"[Pursuer]Error:" + e);
			}
		}
	}
}
