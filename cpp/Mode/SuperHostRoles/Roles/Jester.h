#pragma once

#include <vector>
#include <stdexcept>

using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class Jester
	{
	public:
		static void WrapUp(GameData::PlayerInfo *exiled);
	};
}
