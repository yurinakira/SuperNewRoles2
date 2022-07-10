#pragma once

#include <vector>
#include <stdexcept>

using namespace Hazel;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Roles
{
	class FalseCharges final
	{
	public:
		static void WrapUp(PlayerControl *exiled);
	};
}
