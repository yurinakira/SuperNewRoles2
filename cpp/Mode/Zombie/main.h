#pragma once

#include "../../EndGame/EndGame.h"
#include "../SuperHostRoles/EndGameCheck.h"
#include <vector>
#include <algorithm>

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
using namespace SuperNewRoles::EndGame;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::Zombie
{
	class main final
	{
	public:
		static Color *Zombiecolor;
		static Color *Policecolor;
		static std::vector<int> ZombiePlayers;
		static bool IsZombie(PlayerControl *player);
		static void CountTaskZombie(GameData *__instance);
		static void SetZombie(PlayerControl *player);
		static void SetNotZombie(PlayerControl *player);
		static bool EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static void ClearAndReload();
		static void SetTimer();
	};
}
