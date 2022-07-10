#pragma once

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class ReportDeadBody
	{
	public:
		static bool ReportDeadBodyPatch(PlayerControl *__instance, GameData::PlayerInfo *target);
	};
}
