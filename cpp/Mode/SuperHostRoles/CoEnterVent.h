#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class CoEnterVent
	{
	public:
		static bool Prefix(PlayerPhysics *__instance, int id);
	};
}
