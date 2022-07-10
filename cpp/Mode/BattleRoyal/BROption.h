#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::BattleRoyal
{
	class BROption
	{
	public:
		static CustomOption::CustomOption *BattleRoyalMode;
		static CustomOption::CustomOption *IsViewAlivePlayer;
		static CustomOption::CustomOption *StartSeconds;
		static CustomOption::CustomOption *IsTeamBattle;
		static CustomOption::CustomOption *TeamAmount;
		static void Load();
	};
}
