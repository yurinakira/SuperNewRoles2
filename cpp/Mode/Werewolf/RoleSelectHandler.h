#pragma once

#include <vector>
#include "../../stringhelper.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Werewolf
{
	class RoleSelectHandler final
	{
	public:
		static void RoleSelect();
		static void OneOrNotListSet();
	};
}
