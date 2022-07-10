#pragma once

#include <vector>
#include <algorithm>
#include "../stringhelper.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{
	class BlackCat
	{
	public:
		static std::vector<unsigned char> CheckedImpostor;
		static bool CheckImpostor(PlayerControl *p);
	};
}
