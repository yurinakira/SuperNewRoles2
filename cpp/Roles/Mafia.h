#pragma once

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{
	class Mafia
	{
	public:
		static bool IsKillFlag();
		static void FixedUpdate();
	};
}
