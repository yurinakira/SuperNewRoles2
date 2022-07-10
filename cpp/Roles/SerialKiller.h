#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <string>
#include <vector>
#include <limits>

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class SerialKiller final
	{
	public:
		static void SHRFixedUpdate(RoleId role);
		static void FixedUpdate();
		static void MurderPlayer(PlayerControl *__instance, PlayerControl *target);
		static void WrapUp();
	};
}
