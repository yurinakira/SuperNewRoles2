#pragma once

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{
	class Levelinger final
	{
	public:
		static void MurderPlayer(PlayerControl *__instance, PlayerControl *target);
		static void LevelingerRevive();
	};
}
