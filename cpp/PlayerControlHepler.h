#pragma once

#include "Patch/ShareGameVersion.h"
#include <string>
#include <vector>
#include <any>
#include "stringhelper.h"

using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
using namespace SuperNewRoles::Patch;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.Patch.ShareGameVersion;

namespace SuperNewRoles
{
	class PlayerControlHepler final
	{
	public:
		static bool IsMod(PlayerControl *player);
		static bool IsMod(ClientData *player);
		static bool IsMod(int player);
		static void clearAllTasks(PlayerControl *player);
		static void refreshRoleDescription(PlayerControl *player);
	};
}
