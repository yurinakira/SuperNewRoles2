#pragma once

#include <optional>

using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{
	class RedRidingHood
	{
	public:
		static void WrapUp(GameData::PlayerInfo *player);
	};
}
