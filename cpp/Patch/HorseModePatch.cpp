#include "HorseModePatch.h"
#include "../Config.h"
#include "ClientOptionsPatch.h"
#include "../ModHelpers.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace static UnityEngine::UI::Button;

namespace SuperNewRoles::Patches
{

bool MainMenuPatch::horseButtonState = HorseModeOption::enableHorseMode;
Sprite *MainMenuPatch::horseModeOffSprite = nullptr;
Sprite *MainMenuPatch::horseModeOnSprite = nullptr;

	void MainMenuPatch::Prefix(MainMenuManager *__instance)
	{
		// Horse mode stuff
		auto horseModeSelectionBehavior = new ClientOptionsPatch::SelectionBehaviour(L"Enable Horse Mode", [&] ()
		{
			HorseModeOption::enableHorseMode = ConfigRoles::getEnableHorseMode()->Value = !ConfigRoles::getEnableHorseMode()->Value;
		}, ConfigRoles::getEnableHorseMode()->Value);

		auto bottomTemplate = GameObject::Find(L"InventoryButton");
		if (bottomTemplate == nullptr)
		{
			delete horseModeSelectionBehavior;
			return;
		}
		auto horseButton = UnityEngine::Object::Instantiate(bottomTemplate, bottomTemplate->transform.parent);
		auto passiveHorseButton = horseButton->GetComponent<PassiveButton*>();
		auto spriteHorseButton = horseButton->GetComponent<SpriteRenderer*>();

		horseModeOffSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.HorseModeButtonOff.png", 75.0f);
		horseModeOnSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.HorseModeButtonOn.png", 75.0f);

		spriteHorseButton->sprite = horseButtonState ? horseModeOnSprite : horseModeOffSprite;

		passiveHorseButton->OnClick = new ButtonClickedEvent();

		passiveHorseButton->OnClick.AddListener(static_cast<UnityEngine::Events::UnityAction*>([&] ()
		{
			horseButtonState = horseModeSelectionBehavior->OnClick();
			if (horseButtonState)
			{
				if (horseModeOnSprite == nullptr)
				{
					horseModeOnSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.HorseModeButtonOn.png", 75.0f);
				}
				spriteHorseButton->sprite = horseModeOnSprite;
			}
			else
			{
				if (horseModeOffSprite == nullptr)
				{
					horseModeOffSprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.HorseModeButtonOff.png", 75.0f);
				}
				spriteHorseButton->sprite = horseModeOffSprite;
			}
			CredentialsPatch::LogoPatch::updateSprite();
			// Avoid wrong Player Particles floating around in the background
			auto particles = GameObject::FindObjectOfType<PlayerParticles*>();
			if (particles != nullptr)
			{
				particles->pool.ReclaimAll();
				particles->Start();
			}
		}));


		auto CreditsButton = UnityEngine::Object::Instantiate(bottomTemplate, bottomTemplate->transform.parent);
		auto passiveCreditsButton = CreditsButton->GetComponent<PassiveButton*>();
		auto spriteCreditsButton = CreditsButton->GetComponent<SpriteRenderer*>();

		spriteCreditsButton->sprite = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.CreditsButton.png", 75.0f);

		passiveCreditsButton->OnClick = new ButtonClickedEvent();

		passiveCreditsButton->OnClick.AddListener(static_cast<UnityEngine::Events::UnityAction*>([&] ()
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"クリック");
			if (CredentialsPatch::LogoPatch::CreditsPopup != nullptr)
			{
				CredentialsPatch::LogoPatch::CreditsPopup->SetActive(true);
			}
		}));

		delete horseModeSelectionBehavior;
	}

bool HorseModeOption::enableHorseMode = false;

	void HorseModeOption::clearAndReloadMapOptions()
	{
		enableHorseMode = ConfigRoles::getEnableHorseMode()->Value;
	}
}
