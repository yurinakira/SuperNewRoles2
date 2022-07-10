#include "BROption.h"
#include "../ModeHandler.h"

using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::BattleRoyal
{

CustomOption::CustomOption *BROption::BattleRoyalMode;
CustomOption::CustomOption *BROption::IsViewAlivePlayer;
CustomOption::CustomOption *BROption::StartSeconds;
CustomOption::CustomOption *BROption::IsTeamBattle;
CustomOption::CustomOption *BROption::TeamAmount;

	void BROption::Load()
	{
		BattleRoyalMode = CustomOption::CustomOption::Create(479, true, CustomOptionType::Generic, L"SettingBattleRoyalMode", false, ModeHandler::ModeSetting);
		IsViewAlivePlayer = CustomOption::CustomOption::Create(480, true, CustomOptionType::Generic, L"BattleRoyalIsViewAlivePlayer", false, BattleRoyalMode);
		StartSeconds = CustomOption::CustomOption::Create(481, true, CustomOptionType::Generic, L"BattleRoyalStartSeconds", 0.0f, 0.0f, 45.0f, 2.5f, BattleRoyalMode);
		IsTeamBattle = CustomOption::CustomOption::Create(482, true, CustomOptionType::Generic, L"BattleRoyalIsTeamBattle", false, BattleRoyalMode);
		TeamAmount = CustomOption::CustomOption::Create(483, true, CustomOptionType::Generic, L"BattleRoyalTeamAmount", 2.0f, 2.0f, 8.0f, 1.0f, IsTeamBattle);
	}
}
