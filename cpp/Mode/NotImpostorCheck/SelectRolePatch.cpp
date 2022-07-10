#include "SelectRolePatch.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../../Main.h"
#include "../../ModHelpers.h"
#include "main.h"
#include "../SuperHostRoles/main.h"
#include "../SuperHostRoles/Helpers.h"

using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Mode::NotImpostorCheck
{

	void SelectRolePatch::SetDesync()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isImpostor(p))
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"[NotImpostorCheck] ImpostorName:" + SuperNewRoles::ModHelpers::nameText(p)->text);
				main::Impostors.push_back(p->PlayerId);
			}
		}
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (std::find(main::Impostors.begin(), main::Impostors.end(), p->PlayerId) != main::Impostors.end())
			{
				if (p->PlayerId != 0)
				{
					SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(p, RoleTypes::Impostor); //p.Data.Role.Role);
					for (auto pc : CachedPlayer::AllPlayers)
					{
						if (std::find(main::Impostors.begin(), main::Impostors.end(), pc->PlayerId) != main::Impostors.end())
						{
							SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(p, RoleTypes::Scientist, pc);
						}
						else
						{
							SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(p, RoleTypes::Impostor, pc);
						}
						SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(pc->PlayerControl, RoleTypes::Scientist, p);
						DestroyableSingleton<RoleManager*>::Instance->SetRole(pc, RoleTypes::Crewmate);
					}
				}
				else
				{
					DestroyableSingleton<RoleManager*>::Instance->SetRole(PlayerControl::LocalPlayer, RoleTypes::Impostor); //p.Data.Role.Role);
					for (auto pc : CachedPlayer::AllPlayers)
					{
						if (pc->PlayerId != 0)
						{
							if (std::find(main::Impostors.begin(), main::Impostors.end(), pc->PlayerId) != main::Impostors.end())
							{
								SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(p, RoleTypes::Scientist, pc);
							}
							else
							{
								SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(p, RoleTypes::Impostor, pc);
							}
							DestroyableSingleton<RoleManager*>::Instance->SetRole(PlayerControl::LocalPlayer, RoleTypes::Crewmate);
						}
					}
				}
			}
			else
			{
				p->RpcSetRole(p->Data->Role.Role);
			}
		}
	}
}
