#pragma once

#include "../../CustomRPC/CustomRPCSender.h"

using namespace Hazel;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class Helpers final
	{
	public:
		static void UnCheckedRpcSetRole(PlayerControl *player, RoleTypes *role);
		//TownOfHostより！！
		static void RpcSetRoleDesync(PlayerControl *player, RoleTypes *role, PlayerControl *seer = nullptr);
		static void RpcSetRoleDesync(PlayerControl *player, CustomRpcSender *sender, RoleTypes *role, PlayerControl *seer = nullptr);
		static void RpcSetRole(PlayerControl *player, CustomRpcSender *sender, RoleTypes *role);
	};
}
