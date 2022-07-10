//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Buttons.h"
#include "../Roles/Sheriff.h"
#include "../Roles/Clergyman.h"
#include "../Roles/Teleporter.h"
#include "../Roles/Jackal.h"
#include "../Patch/PlayerControlPatch.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleClass.h"
#include "../TranslateDate.h"
#include "../Helpers/FastDestroyableSingleton.h"

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

CustomButton *HudManagerStartPatch::SheriffKillButton;
CustomButton *HudManagerStartPatch::ClergymanLightOutButton;
CustomButton *HudManagerStartPatch::SpeedBoosterBoostButton;
CustomButton *HudManagerStartPatch::EvilSpeedBoosterBoostButton;
CustomButton *HudManagerStartPatch::LighterLightOnButton;
CustomButton *HudManagerStartPatch::MovingSetButton;
CustomButton *HudManagerStartPatch::MovingTpButton;
CustomButton *HudManagerStartPatch::TeleporterButton;
CustomButton *HudManagerStartPatch::DoorrDoorButton;
CustomButton *HudManagerStartPatch::SelfBomberButton;
CustomButton *HudManagerStartPatch::DoctorVitalsButton;
CustomButton *HudManagerStartPatch::CountChangerButton;
CustomButton *HudManagerStartPatch::ScientistButton;
CustomButton *HudManagerStartPatch::HawkHawkEyeButton;
CustomButton *HudManagerStartPatch::JackalKillButton;
CustomButton *HudManagerStartPatch::JackalSidekickButton;
CustomButton *HudManagerStartPatch::JackalSeerSidekickButton;
CustomButton *HudManagerStartPatch::MagazinerAddButton;
CustomButton *HudManagerStartPatch::MagazinerGetButton;
CustomButton *HudManagerStartPatch::trueloverLoveButton;
CustomButton *HudManagerStartPatch::ImpostorSidekickButton;
CustomButton *HudManagerStartPatch::SideKillerSidekickButton;
CustomButton *HudManagerStartPatch::FalseChargesFalseChargeButton;
CustomButton *HudManagerStartPatch::MadMakerSidekickButton;
CustomButton *HudManagerStartPatch::DemonButton;
CustomButton *HudManagerStartPatch::ArsonistDouseButton;
CustomButton *HudManagerStartPatch::ArsonistIgniteButton;
CustomButton *HudManagerStartPatch::SpeederButton;
CustomButton *HudManagerStartPatch::ChiefSidekickButton;
CustomButton *HudManagerStartPatch::VultureButton;
CustomButton *HudManagerStartPatch::ShielderButton;
CustomButton *HudManagerStartPatch::CleanerButton;
CustomButton *HudManagerStartPatch::MadCleanerButton;
CustomButton *HudManagerStartPatch::FreezerButton;
CustomButton *HudManagerStartPatch::SamuraiButton;
CustomButton *HudManagerStartPatch::VentMakerButton;
CustomButton *HudManagerStartPatch::GhostMechanicRepairButton;
CustomButton *HudManagerStartPatch::EvilHackerButton;
CustomButton *HudManagerStartPatch::EvilHackerMadmateSetting;
CustomButton *HudManagerStartPatch::PositionSwapperButton;
CustomButton *HudManagerStartPatch::KunoichiKunaiButton;
CustomButton *HudManagerStartPatch::SecretlyKillerMainButton;
CustomButton *HudManagerStartPatch::SecretlyKillerSecretlyKillButton;
CustomButton *HudManagerStartPatch::ClairvoyantButton;
CustomButton *HudManagerStartPatch::DoubleKillerMainKillButton;
CustomButton *HudManagerStartPatch::DoubleKillerSubKillButton;
CustomButton *HudManagerStartPatch::SuicideWisherSuicideButton;
CustomButton *HudManagerStartPatch::FastMakerButton;
TMPro::TMP_Text *HudManagerStartPatch::sheriffNumShotsText;
TMPro::TMP_Text *HudManagerStartPatch::GhostMechanicNumRepairText;
TMPro::TMP_Text *HudManagerStartPatch::PositionSwapperNumText;
TMPro::TMP_Text *HudManagerStartPatch::SecretlyKillNumText;

	void HudManagerStartPatch::setCustomButtonCooldowns()
	{
		Sheriff::ResetKillCoolDown();
		Clergyman::ResetCoolDown();
		Teleporter::ResetCoolDown();
		Jackal::resetCoolDown();
		//クールダウンリセット
	}

	PlayerControl *HudManagerStartPatch::setTarget(std::vector<PlayerControl*> &untarget, bool Crewmateonly)
	{
		return PlayerControlFixedUpdatePatch::setTarget(Crewmateonly, false, untarget, nullptr);
	}

	void HudManagerStartPatch::Postfix(HudManager *__instance)
	{
		Vector3 tempVar(-1.8f, -0.06f, 0);
		KunoichiKunaiButton = new CustomButton([&] ()
		{
				if (RoleClass::Kunoichi::Kunai->kunai->active)
				{
					RoleClass::Kunoichi::Kunai->kunai->SetActive(false);
				}
				else
				{
					RoleClass::Kunoichi::Kunai->kunai->SetActive(true);
				}
		}, [&] (bool isAlive, RoleId role)
		{
				return isAlive && role == RoleId::Kunoichi;
			}, [&] ()
			{
				return PlayerControl::LocalPlayer::CanMove;
			}, [&] ()
			{
				KunoichiKunaiButton->MaxTimer = 0.0f;
				KunoichiKunaiButton->Timer = 0.0f;
			}, RoleClass::Kunoichi::getButtonSprite(), &tempVar, __instance, __instance->AbilityButton, KeyCode::F, 49, [&] ()
			{
				return false;
			});
		KunoichiKunaiButton->buttonText = ModTranslation::getString(L"KunoichiKunai");
		KunoichiKunaiButton->showButtonText = true;
		Vector3 tempVar2(0, 1, 0);
		FalseChargesFalseChargeButton = new CustomButton([&] ()
		{
				if (setTarget() && RoleHelpers::isAlive(PlayerControl::LocalPlayer) && PlayerControl::LocalPlayer::CanMove)
				{
					if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
					{
						PlayerControl::LocalPlayer::CmdCheckMurder(setTarget());
					}
					else
					{
						ModHelpers::UncheckedMurderPlayer(setTarget(), PlayerControl::LocalPlayer);
						RoleClass::FalseCharges::FalseChargePlayer = setTarget()->PlayerId;
						RoleClass::FalseCharges::Turns = RoleClass::FalseCharges::DefaultTurn;
					}
				}
		}, [&] (bool isAlive, RoleId role)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
