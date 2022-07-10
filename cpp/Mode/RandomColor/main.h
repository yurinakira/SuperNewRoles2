#pragma once

#include "../../EndGame/EndGame.h"

using namespace SuperNewRoles::EndGame;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::RandomColor
{
	class main
	{
	public:
		static bool CheckEndGame(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static void CustomEndGame(ShipStatus *__instance, GameOverReason *reason, bool showAd);
		static bool CheckAndEndGameForSabotageWin(ShipStatus *__instance);

		static bool CheckAndEndGameForTaskWin(ShipStatus *__instance);

		static bool CheckAndEndGameForImpostorWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);

		static bool CheckAndEndGameForCrewmateWin(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static void EndGameForSabotage(ShipStatus *__instance);
	};
}
