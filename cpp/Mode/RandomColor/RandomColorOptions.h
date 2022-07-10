#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::RandomColor
{
	class RandomColorOptions
	{
	public:
		static CustomOption::CustomOption *RandomColorMode;
		static CustomOption::CustomOption *HideName;
		static CustomOption::CustomOption *RandomNameColor;
		static CustomOption::CustomOption *RandomColorMeeting;
		static void Load();
	};
}
