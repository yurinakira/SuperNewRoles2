#pragma once

#include "../../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Detective
{
	class DetectiveOptions
	{
	public:
		static CustomOption::CustomOption *DetectiveMode;
		static CustomOption::CustomOption *IsWinNotCheckDetective;
		static CustomOption::CustomOption *DetectiveIsNotTask;
		static CustomOption::CustomOption *IsNotDetectiveVote;
		static CustomOption::CustomOption *IsNotDetectiveMeetingButton;
		static void Load();
	};
}
