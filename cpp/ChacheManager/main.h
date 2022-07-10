#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <unordered_map>

using namespace SuperNewRoles::CustomRPC;

namespace SuperNewRoles
{
	class ChacheManager
	{
	public:
		static std::unordered_map<int, RoleId> MyRoleChache;
		static std::unordered_map<int, RoleId> MyGhostRoleChache;
		static std::unordered_map<int, PlayerControl*> LoversChache;
		static std::unordered_map<int, PlayerControl*> QuarreledChache;
		static void Load();
		static void ResetChache();
		static void ResetQuarreledChache();
		static void ResetLoversChache();
		static void ResetMyRoleChache();
		static void ResetMyGhostRoleChache();
	};
}
