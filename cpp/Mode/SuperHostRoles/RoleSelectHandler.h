#pragma once

#include "../../CustomRPC/CustomRPCSender.h"
#include <vector>

using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class RoleSelectHandler final
	{
	public:
		static CustomRpcSender *sender;
		static CustomRpcSender *RoleSelect(CustomRpcSender *send);
		static void SpawnBots();
		static void SetCustomRoles();
		static void CrewOrImpostorSet();
		static void OneOrNotListSet();
	};
}
