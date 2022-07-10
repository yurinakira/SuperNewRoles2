#include "HASOptions.h"
#include "../ModeHandler.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{

CustomOption::CustomOption *ZombieOptions::HideAndSeekMode;
CustomOption::CustomOption *ZombieOptions::HASDeathTask;
CustomOption::CustomOption *ZombieOptions::HASUseSabo;
CustomOption::CustomOption *ZombieOptions::HASUseVent;

	void ZombieOptions::Load()
	{
		HideAndSeekMode = CustomOption::CustomOption::Create(475, true, CustomOptionType::Generic, L"SettingHideAndSeekMode", false, ModeHandler::ModeSetting);
		HASDeathTask = CustomOption::CustomOption::Create(476, true, CustomOptionType::Generic, L"HASDeathTaskSetting", false, HideAndSeekMode);
		HASUseSabo = CustomOption::CustomOption::Create(477, true, CustomOptionType::Generic, L"HASUseSaboSetting", false, HideAndSeekMode);
		HASUseVent = CustomOption::CustomOption::Create(478, true, CustomOptionType::Generic, L"HASUseVentSetting", false, HideAndSeekMode);
	}
}
