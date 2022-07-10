#pragma once

#include <vector>
#include <algorithm>

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles

{
	class JackalFriends
	{
	public:
		static std::vector<unsigned char> CheckedJackal;
		static bool CheckJackal(PlayerControl *p);
	};
}
