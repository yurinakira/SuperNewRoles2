#pragma once

#include "../CustomOption/CustomOptionModel.h"

using namespace SuperNewRoles::CustomOption;

namespace SuperNewRoles::Sabotage
{
	class Options final
	{
	public:
		static CustomOption::CustomOption *SabotageSetting;
		static CustomOption::CustomOption *CognitiveDeficitSetting;
		static CustomOption::CustomOption *CognitiveDeficitOutfitUpdateTimeSetting;
		static CustomOption::CustomOption *CognitiveDeficitReleaseTimeSetting;
		static CustomOption::CustomOption *CognitiveDeficitIsAllEndSabotageSetting;
		static void Load();
	};
}
