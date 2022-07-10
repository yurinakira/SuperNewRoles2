#pragma once

#include <vector>

using namespace Hazel;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{
	class Nekomata
	{
	public:
		static void NekomataEnd(GameData::PlayerInfo *__instance);
		static void NekomataProc(std::vector<PlayerControl*> &p);
	};
}
