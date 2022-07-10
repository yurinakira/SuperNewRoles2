#include "Options.h"

using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Mode::PlusMode
{

CustomOption::CustomOption *Options::PlusModeSetting;
CustomOption::CustomOption *Options::NoSabotageModeSetting;
CustomOption::CustomOption *Options::NoTaskWinModeSetting;

	void Options::Load()
	{
		PlusModeSetting = CustomOption::CustomOption::Create(508, true, CustomOptionType::Generic, L"PlusModeSetting", false, nullptr, true, false, L"");
		NoSabotageModeSetting = CustomOption::CustomOption::Create(509, true, CustomOptionType::Generic, L"SettingNoSabotageMode", false, PlusModeSetting);
		NoTaskWinModeSetting = CustomOption::CustomOption::Create(510, true, CustomOptionType::Generic, L"SettingNoTaskWinMode", false, PlusModeSetting);
		//FixedSpawnSetting = CustomOption.CustomOption.Create(511, ModTranslation.getString("SettingFixedSpawnMode"), false, PlusModeSetting);
	}
}
