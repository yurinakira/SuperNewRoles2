#include "WerewolfOptions.h"
#include "../ModeHandler.h"
#include "../../CustomOption/CustomOptionDate.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Werewolf
{

CustomOption::CustomOption *WerewolfOptions::WerewolfMode;
CustomOption::CustomOption *WerewolfOptions::WerewolfHunterOption;

	void WerewolfOptions::Load()
	{
		WerewolfMode = CustomOption::CustomOption::Create(506, true, CustomOptionType::Generic, L"SettingWerewolfMode", false, ModeHandler::ModeSetting);
		WerewolfHunterOption = CustomOption::CustomOption::Create(507, true, CustomOptionType::Generic, L"HunterName", CustomOptions::rates, WerewolfMode);
	}
}
