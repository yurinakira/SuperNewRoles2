#pragma once

#include "../../EndGame/EndGame.h"
#include <vector>

using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class WrapUpClass
	{
	public:
		static void WrapUp(GameData::PlayerInfo *exiled);
	};
}
