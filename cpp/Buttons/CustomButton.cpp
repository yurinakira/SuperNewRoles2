//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomButton.h"
#include "../Config.h"
#include "../Helpers/CachedPlayer.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Buttons
{

std::vector<CustomButton*> CustomButton::buttons;

	CustomButton::CustomButton(std::function<void()> OnClick, std::function<bool(bool, RoleId)> HasButton, std::function<bool()> CouldUse, std::function<void()> OnMeetingEnds, Sprite *Sprite, Vector3 *PositionOffset, HudManager *hudManager, ActionButton *textTemplate, std::optional<KeyCode*> &hotkey, int joystickkey, std::function<bool()> StopCountCool, bool HasEffect, float EffectDuration, std::function<void()> OnEffectEnds, bool mirror, const std::wstring &buttonText)
	{
		this->hudManager = hudManager;
		this->OnClick = OnClick;
		this->HasButton = HasButton;
		this->CouldUse = CouldUse;
		this->PositionOffset = PositionOffset;
		this->OnMeetingEnds = OnMeetingEnds;
		this->HasEffect = HasEffect;
		this->EffectDuration = EffectDuration;
		this->OnEffectEnds = OnEffectEnds;
		this->Sprite = Sprite;
		this->mirror = mirror;
		this->hotkey = hotkey;
		this->joystickkey = joystickkey;
		this->buttonText = buttonText;
		this->StopCountCool = StopCountCool;
		Timer = 16.2f;
		buttons.push_back(this);
		actionButton = UnityEngine::Object::Instantiate(textTemplate, textTemplate->transform.parent);
		PassiveButton *button = actionButton->GetComponent<PassiveButton*>();
		button->OnClick = new Button::ButtonClickedEvent();

		button->OnClick.AddListener(static_cast<UnityEngine::Events::UnityAction*>(onClickEvent));

		LocalScale = actionButton->transform.localScale;
		if (textTemplate)
		{
			UnityEngine::Object::Destroy(actionButton->buttonLabelText);
			actionButton->buttonLabelText = UnityEngine::Object::Instantiate(textTemplate->buttonLabelText, actionButton->transform);
		}
		setActive(false);
	}
}

void <missing_class_definition>::HudUpdate()
{
	buttons::RemoveAll([&] (std::any item)
	{
		return item->actionButton == nullptr;
	});

	bool isAlive = PlayerControl::LocalPlayer::isAlive();
	RoleId role = PlayerControl::LocalPlayer::getRole();
	for (CustomButton *btn : buttons)
	{
		try
		{
			btn->Update(isAlive, role);
		}
		catch (const std::runtime_error &e)
		{
			std::wcout << L"ButtonError:" << e << std::endl;
		}
	}
}

void <missing_class_definition>::MeetingEndedUpdate()
{
	buttons::RemoveAll([&] (std::any item)
	{
		return item->actionButton == nullptr;
	});
	bool isAlive = PlayerControl::LocalPlayer::isAlive();
	RoleId role = PlayerControl::LocalPlayer::getRole();
	for (CustomButton *btn : buttons)
	{
		try
		{
			if (btn->HasButton(isAlive, role))
			{
				btn->OnMeetingEnds();
				btn->Update(isAlive, role);
			}
		}
		catch (const std::runtime_error &e)
		{
			if (ConfigRoles::getDebugMode()->Value)
			{
				std::wcout << L"MeetingEnd_ButtonError:" << e << std::endl;
			}
		}
	}
}

void <missing_class_definition>::setActive(bool isActive)
{
	if (isActive)
	{
		actionButton::gameObject::SetActive(true);
		actionButton::graphic->enabled = true;
	}
	else
	{
		actionButton::gameObject::SetActive(false);
		actionButton::graphic->enabled = false;
	}
}

void <missing_class_definition>::Update(bool isAlive, RoleId role)
{
	auto localPlayer = CachedPlayer::LocalPlayer;
	auto moveable = localPlayer->PlayerControl->moveable;

	if (localPlayer->Data == nullptr || MeetingHud::Instance || ExileController::Instance || !HasButton(isAlive, role))
	{
		setActive(false);
		return;
	}
	setActive(hudManager::UseButton::isActiveAndEnabled);

	actionButton::graphic->sprite = Sprite;
	if (showButtonText && buttonText != L"")
	{
		actionButton::OverrideText(buttonText);
	}
	actionButton::buttonLabelText->enabled = showButtonText; // Only show the text if it's a kill button

	if (hudManager::UseButton != nullptr)
	{
		Vector3 *pos = hudManager::UseButton::transform::localPosition;
		if (mirror)
		{
			pos = new Vector3(-pos->x, pos->y, pos->z);
		}
		actionButton::transform->localPosition = pos + PositionOffset;

//C# TO C++ CONVERTER TODO TASK: A 'delete pos' statement was not added since pos was assigned to another object. Handle memory management manually.
	}
	if (CouldUse())
	{
		actionButton::graphic->color = actionButton::buttonLabelText->color = Palette->EnabledColor;
		actionButton::graphic::material::SetFloat(L"_Desat", 0.0f);
	}
	else
	{
		actionButton::graphic->color = actionButton::buttonLabelText->color = Palette->DisabledClear;
		actionButton::graphic::material::SetFloat(L"_Desat", 1.0f);
	}

	if (Timer >= 0)
	{
		if ((HasEffect && isEffectActive) || (!localPlayer->PlayerControl->inVent && moveable && !StopCountCool()))
		{
			Timer -= Time::deltaTime;
		}
	}

	if (Timer <= 0 && HasEffect && isEffectActive)
	{
		isEffectActive = false;
		actionButton::cooldownTimerText->color = Palette->EnabledColor;
		OnEffectEnds();
	}

	actionButton::SetCoolDown(Timer, (HasEffect && isEffectActive) ? EffectDuration : MaxTimer);
	// Trigger OnClickEvent if the hotkey is being pressed down
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
	if ((hotkey.HasValue && Input->GetButtonDown(hotkey->Value->ToString())) || ConsoleJoystick::player::GetButtonDown(joystickkey))
	{
		onClickEvent();
	}
}

void HudManagerUpdatePatch::Postfix(HudManager *__instance)
{
	if (AmongUsClient::Instance->GameState != InnerNet::InnerNetClient::GameStates::Started)
	{
		return;
	}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
