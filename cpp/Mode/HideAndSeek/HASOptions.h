#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{
	class ZombieOptions
	{
	public:
		static CustomOption::CustomOption *HideAndSeekMode;
		static CustomOption::CustomOption *HASDeathTask;
		static CustomOption::CustomOption *HASUseSabo;
		static CustomOption::CustomOption *HASUseVent;
		static void Load();
	};
}
