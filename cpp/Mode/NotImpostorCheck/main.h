#pragma once

#include "../../EndGame/EndGame.h"
#include <vector>

using namespace SuperNewRoles::EndGame;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static SuperNewRoles.EndGame.CheckGameEndPatch;

namespace SuperNewRoles::Mode::NotImpostorCheck
{
	class main
	{
	public:
		static std::vector<int> Impostors;
		static void ClearAndReload();
	};
}
