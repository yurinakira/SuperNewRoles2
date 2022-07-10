#pragma once

#include "../../EndGame/EndGame.h"

using namespace SuperNewRoles::EndGame;
using namespace UnityEngine;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::HideAndSeek
{
	class main
	{
	public:
		static bool EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics);
		static void ClearAndReload();
	};
}
