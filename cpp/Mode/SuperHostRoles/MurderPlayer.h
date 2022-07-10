#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class MurderPlayer
	{
	public:
		static void Postfix(PlayerControl *__instance, PlayerControl *target);
	};
}
