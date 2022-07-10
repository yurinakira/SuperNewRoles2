#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Werewolf
{
	class WerewolfOptions
	{
	public:
		static CustomOption::CustomOption *WerewolfMode;
		static CustomOption::CustomOption *WerewolfHunterOption;
		static void Load();
	};
}
