#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{
	class Nekomata
	{
	public:
		static void WrapUp(GameData::PlayerInfo *exiled);
		static void NekomataEnd(GameData::PlayerInfo *exiled);
		static void NekomataProc(std::vector<PlayerControl*> &p);
	};
}
