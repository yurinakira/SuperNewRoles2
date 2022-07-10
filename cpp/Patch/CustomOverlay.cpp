//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomOverlay.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../ModHelpers.h"
#include "../Helpers/MapUtilities.h"
#include "../Main.h"
#include "../CustomOption/CustomOptionModel.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomOption;
using namespace UnityEngine;

namespace SuperNewRoles::Patch
{

Sprite *CustomOverlays::helpButton;
Sprite *CustomOverlays::colorBG;
SpriteRenderer *CustomOverlays::meetingUnderlay;
SpriteRenderer *CustomOverlays::infoUnderlay;
TMPro::TextMeshPro *CustomOverlays::infoOverlayRules;
TMPro::TextMeshPro *CustomOverlays::infoOverlayRoles;
bool CustomOverlays::overlayShown = false;

	void CustomOverlays::resetOverlays()
	{
		hideBlackBG();
		hideInfoOverlay();
		UnityEngine::Object::Destroy(meetingUnderlay);
		UnityEngine::Object::Destroy(infoUnderlay);
		UnityEngine::Object::Destroy(infoOverlayRules);
		UnityEngine::Object::Destroy(infoOverlayRoles);
		meetingUnderlay = infoUnderlay = nullptr;
		infoOverlayRules = infoOverlayRoles = nullptr;
		overlayShown = false;
	}

	bool CustomOverlays::initializeOverlays()
	{
		HudManager *hudManager = FastDestroyableSingleton<HudManager*>::getInstance();
		if (hudManager == nullptr)
		{
			return false;
		}

		if (helpButton == nullptr)
		{
			helpButton = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.HelpButton.png", 115.0f);
		}

		if (colorBG == nullptr)
		{
			colorBG = ModHelpers::loadSpriteFromResources(L"SuperNewRoles.Resources.White.png", 100.0f);
		}

		if (meetingUnderlay == nullptr)
		{
			meetingUnderlay = UnityEngine::Object::Instantiate(hudManager->FullScreen, hudManager->transform);
			meetingUnderlay->transform->localPosition = new Vector3(0.0f, 0.0f, 20.0f);
			meetingUnderlay->gameObject.SetActive(true);
			meetingUnderlay->enabled = false;
		}

		if (infoUnderlay == nullptr)
		{
			infoUnderlay = UnityEngine::Object::Instantiate(meetingUnderlay, hudManager->transform);
			infoUnderlay->transform->localPosition = new Vector3(0.0f, 0.0f, -900.0f);
			infoUnderlay->gameObject.SetActive(true);
			infoUnderlay->enabled = false;
		}

		if (infoOverlayRules == nullptr)
		{
			infoOverlayRules = UnityEngine::Object::Instantiate(hudManager->TaskText, hudManager->transform);
			infoOverlayRules->fontSize = infoOverlayRules->fontSizeMin = infoOverlayRules->fontSizeMax = 1.15f;
			infoOverlayRules->autoSizeTextContainer = false;
			infoOverlayRules->enableWordWrapping = false;
			infoOverlayRules->alignment = TMPro::TextAlignmentOptions::TopLeft;
			infoOverlayRules->transform->position = Vector3::zero;
			infoOverlayRules->transform->localPosition = new Vector3(-2.5f, 1.15f, -910.0f);
			infoOverlayRules->transform->localScale = Vector3::one;
			infoOverlayRules->color = Palette->White;
			infoOverlayRules->enabled = false;
		}

		if (infoOverlayRoles == nullptr)
		{
			infoOverlayRoles = UnityEngine::Object::Instantiate(infoOverlayRules, hudManager->transform);
			infoOverlayRoles->maxVisibleLines = 28;
			infoOverlayRoles->fontSize = infoOverlayRoles->fontSizeMin = infoOverlayRoles->fontSizeMax = 1.15f;
			infoOverlayRoles->outlineWidth += 0.02f;
			infoOverlayRoles->autoSizeTextContainer = false;
			infoOverlayRoles->enableWordWrapping = false;
			infoOverlayRoles->alignment = TMPro::TextAlignmentOptions::TopLeft;
			infoOverlayRoles->transform->position = Vector3::zero;
			infoOverlayRoles->transform->localPosition = infoOverlayRules->transform.localPosition + new Vector3(2.5f, 0.0f, 0.0f);
			infoOverlayRoles->transform->localScale = Vector3::one;
			infoOverlayRoles->color = Palette->White;
			infoOverlayRoles->enabled = false;
		}
		return true;
	}

	void CustomOverlays::showBlackBG()
	{
		if (FastDestroyableSingleton<HudManager*>::getInstance() == nullptr)
		{
			return;
		}
		if (!initializeOverlays())
		{
			return;
		}

		meetingUnderlay->sprite = colorBG;
		meetingUnderlay->enabled = true;
		meetingUnderlay->transform->localScale = new Vector3(20.0f, 20.0f, 1.0f);
		auto clearBlack = new Color32(0, 0, 0, 0);

		std::function<void(float)> tempVar([&] (std::any t)
		{
			meetingUnderlay->color = Color::Lerp(clearBlack, Palette->Black, t);
		});
		FastDestroyableSingleton<HudManager*>::getInstance().StartCoroutine(Effects::Lerp(0.2f, &tempVar));

//C# TO C++ CONVERTER TODO TASK: A 'delete clearBlack' statement was not added since clearBlack was passed to a method or constructor. Handle memory management manually.
	}

	void CustomOverlays::hideBlackBG()
	{
		if (meetingUnderlay == nullptr)
		{
			return;
		}
		meetingUnderlay->enabled = false;
	}

	void CustomOverlays::showInfoOverlay()
	{
		if (overlayShown)
		{
			return;
		}

		HudManager *hudManager = FastDestroyableSingleton<HudManager*>::getInstance();
		if (MapUtilities::CachedShipStatus == nullptr || PlayerControl->LocalPlayer == nullptr || hudManager == nullptr || FastDestroyableSingleton<HudManager*>::getInstance().IsIntroDisplayed || (!PlayerControl::LocalPlayer::CanMove && MeetingHud->Instance == nullptr))
		{
			return;
		}

		if (!initializeOverlays())
		{
			return;
		}

		if (MapBehaviour::Instance != nullptr)
		{
			MapBehaviour::Instance->Close();
		}

		hudManager->SetHudActive(false);

		overlayShown = true;

		Transform *parent;
		if (MeetingHud::Instance != nullptr)
		{
			parent = MeetingHud::Instance->transform;
		}
		else
		{
			parent = hudManager->transform;
		}

		infoUnderlay->transform->parent = parent;
		infoOverlayRules->transform->parent = parent;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
