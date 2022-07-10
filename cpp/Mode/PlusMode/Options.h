#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Mode::PlusMode
{
	class Options
	{
	public:
		static CustomOption::CustomOption *PlusModeSetting;
		static CustomOption::CustomOption *NoSabotageModeSetting;
		static CustomOption::CustomOption *NoTaskWinModeSetting;
		//public static CustomOption.CustomOption FixedSpawnSetting;
		static void Load();
	};
}
