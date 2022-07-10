#pragma once

#include "CustomButton.h"
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <functional>

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Buttons
{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Start))] static class HudManagerStartPatch
	class HudManagerStartPatch final
	{
	public:
		static CustomButton *SheriffKillButton;
		static CustomButton *ClergymanLightOutButton;
		static CustomButton *SpeedBoosterBoostButton;
		static CustomButton *EvilSpeedBoosterBoostButton;
		static CustomButton *LighterLightOnButton;
		static CustomButton *MovingSetButton;
		static CustomButton *MovingTpButton;
		static CustomButton *TeleporterButton;
		static CustomButton *DoorrDoorButton;
		static CustomButton *SelfBomberButton;
		static CustomButton *DoctorVitalsButton;
		static CustomButton *CountChangerButton;
		static CustomButton *ScientistButton;
		static CustomButton *HawkHawkEyeButton;
		static CustomButton *JackalKillButton;
		static CustomButton *JackalSidekickButton;
		static CustomButton *JackalSeerSidekickButton;
		static CustomButton *MagazinerAddButton;
		static CustomButton *MagazinerGetButton;
		static CustomButton *trueloverLoveButton;
		static CustomButton *ImpostorSidekickButton;
		static CustomButton *SideKillerSidekickButton;
		static CustomButton *FalseChargesFalseChargeButton;
		static CustomButton *MadMakerSidekickButton;
		static CustomButton *DemonButton;
		static CustomButton *ArsonistDouseButton;
		static CustomButton *ArsonistIgniteButton;
		static CustomButton *SpeederButton;
		static CustomButton *ChiefSidekickButton;
		static CustomButton *VultureButton;
		static CustomButton *ShielderButton;
		static CustomButton *CleanerButton;
		static CustomButton *MadCleanerButton;
		static CustomButton *FreezerButton;
		static CustomButton *SamuraiButton;
		static CustomButton *VentMakerButton;
		static CustomButton *GhostMechanicRepairButton;
		static CustomButton *EvilHackerButton;
		static CustomButton *EvilHackerMadmateSetting;
		static CustomButton *PositionSwapperButton;
		static CustomButton *KunoichiKunaiButton;
		static CustomButton *SecretlyKillerMainButton;
		static CustomButton *SecretlyKillerSecretlyKillButton;
		static CustomButton *ClairvoyantButton;
		static CustomButton *DoubleKillerMainKillButton;
		static CustomButton *DoubleKillerSubKillButton;
		static CustomButton *SuicideWisherSuicideButton;
		static CustomButton *FastMakerButton;

		static TMPro::TMP_Text *sheriffNumShotsText;
		static TMPro::TMP_Text *GhostMechanicNumRepairText;
		static TMPro::TMP_Text *PositionSwapperNumText;
		static TMPro::TMP_Text *SecretlyKillNumText;

		static void setCustomButtonCooldowns();

		static PlayerControl *setTarget(std::vector<PlayerControl*> &untarget = std::vector<PlayerControl>(), bool Crewmateonly = false);

		static void Postfix(HudManager *__instance);
	};
}
