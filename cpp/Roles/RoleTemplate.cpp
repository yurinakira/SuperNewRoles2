#include "RoleTemplate.h"

using namespace HarmonyLib;

namespace SuperNewRoles::Roles
{

std::vector<Role*> RoleTemplate::Role::allRoles;

	void RoleTemplate::Role::ResetRole()
	{
	}

	void RoleTemplate::Role::ClearAll()
	{
		allRoles = std::vector<Role*>();
	}
}
