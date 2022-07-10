#pragma once

using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class Bait
	{
	public:
		static void MurderPostfix(PlayerControl *__instance, PlayerControl *target);
	};
}
