#pragma once

#include <vector>
#include <algorithm>

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{
	class Madmate
	{
	public:
		static std::vector<unsigned char> CheckedImpostor;
		static bool CheckImpostor(PlayerControl *p);
	};
}
