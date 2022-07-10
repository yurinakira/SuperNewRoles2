#include "RandomColorOptions.h"
#include "../ModeHandler.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::RandomColor
{

CustomOption::CustomOption *RandomColorOptions::RandomColorMode;
CustomOption::CustomOption *RandomColorOptions::HideName;
CustomOption::CustomOption *RandomColorOptions::RandomNameColor;
CustomOption::CustomOption *RandomColorOptions::RandomColorMeeting;

	void RandomColorOptions::Load()
	{
		RandomColorMode = CustomOption::CustomOption::Create(497, true, CustomOptionType::Generic, L"SettingRandomColorMode", false, ModeHandler::ModeSetting);
		HideName = CustomOption::CustomOption::Create(498, true, CustomOptionType::Generic, L"RandomColorHideNameSetting", false, RandomColorMode);
		RandomNameColor = CustomOption::CustomOption::Create(499, true, CustomOptionType::Generic, L"RandomColorNameColorSetting", true, RandomColorMode);
		RandomColorMeeting = CustomOption::CustomOption::Create(500, true, CustomOptionType::Generic, L"RandomColorMeetingSetting", true, RandomColorMode);
	}
}
