#include "Options.h"

using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Sabotage
{

CustomOption::CustomOption *Options::SabotageSetting;
CustomOption::CustomOption *Options::CognitiveDeficitSetting;
CustomOption::CustomOption *Options::CognitiveDeficitOutfitUpdateTimeSetting;
CustomOption::CustomOption *Options::CognitiveDeficitReleaseTimeSetting;
CustomOption::CustomOption *Options::CognitiveDeficitIsAllEndSabotageSetting;

	void Options::Load()
	{
		SabotageSetting = CustomOption::CustomOption::Create(512, false, CustomOptionType::Generic, L"SabotageSetting", false, nullptr, true, false, L"");
		//
		CognitiveDeficitSetting = CustomOption::CustomOption::Create(513, false, CustomOptionType::Generic, L"SabotageCognitiveDeficitSetting", false, SabotageSetting);
		CognitiveDeficitOutfitUpdateTimeSetting = CustomOption::CustomOption::Create(514, false, CustomOptionType::Generic, L"CognitiveDeficitSabotageOutfitUpdateTimeSetting", 3.0f, 0.5f, 10.0f, 0.5f, CognitiveDeficitSetting);
		CognitiveDeficitReleaseTimeSetting = CustomOption::CustomOption::Create(515, false, CustomOptionType::Generic, L"CognitiveDeficitSabotageReleaseTimeSetting", 3.0f, 0.5f, 10.0f, 0.5f, CognitiveDeficitSetting);
		CognitiveDeficitIsAllEndSabotageSetting = CustomOption::CustomOption::Create(516, false, CustomOptionType::Generic, L"CognitiveDeficitSabotageIsAllPlayerEndSabotageSetting", true, CognitiveDeficitSetting);
	}
}
