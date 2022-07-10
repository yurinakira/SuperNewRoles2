#pragma once

#include "../../EndGame/EndGame.h"
#include <vector>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::SuperHostRoles
{
	class EndGameCheck
	{
	public:
		static bool CheckEndGame(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static void WinNeutral(std::vector<PlayerControl*> &players);
		static void CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd);
		static bool CheckAndEndGameForSabotageWin(ShipStatus *__instance);

		static bool CheckAndEndGameForTaskWin(ShipStatus *__instance);
		static bool CheckAndEndGameForJackalWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);

		static bool CheckAndEndGameForDefaultWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static bool CheckAndEndGameForArsonistWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static bool CheckAndEndGameForCrewmateWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static bool CheckAndEndGameForWorkpersonWin(ShipStatus *__instance);
		static void EndGameForSabotage(ShipStatus *__instance);
	};
}
