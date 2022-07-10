#include "DetectiveOptions.h"
#include "../ModeHandler.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Detective
{

CustomOption::CustomOption *DetectiveOptions::DetectiveMode;
CustomOption::CustomOption *DetectiveOptions::IsWinNotCheckDetective;
CustomOption::CustomOption *DetectiveOptions::DetectiveIsNotTask;
CustomOption::CustomOption *DetectiveOptions::IsNotDetectiveVote;
CustomOption::CustomOption *DetectiveOptions::IsNotDetectiveMeetingButton;

	void DetectiveOptions::Load()
	{
		DetectiveMode = CustomOption::CustomOption::Create(501, true, CustomOptionType::Generic, L"SettingDetectiveMode", false, ModeHandler::ModeSetting);
		IsWinNotCheckDetective = CustomOption::CustomOption::Create(502, true, CustomOptionType::Generic, L"DetectiveModeIsWinNotCheckSetting", false, DetectiveMode);
		DetectiveIsNotTask = CustomOption::CustomOption::Create(503, true, CustomOptionType::Generic, L"DetectiveModeIsNotTaskSetting", false, DetectiveMode);
		IsNotDetectiveVote = CustomOption::CustomOption::Create(504, true, CustomOptionType::Generic, L"DetectiveModeIsNotDetectiveVoteSetting", false, DetectiveMode);
		IsNotDetectiveMeetingButton = CustomOption::CustomOption::Create(505, true, CustomOptionType::Generic, L"DetectiveModeIsNotDetectiveMeetingButtonSetting", false, DetectiveMode);
	}
}
