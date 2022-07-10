#pragma once

#include "../CustomRPC/CustomRPC.h"
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <functional>
#include <optional>

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace SuperNewRoles::Buttons
{
	class CustomButton
	{
	public:
		static std::vector<CustomButton*> buttons;
		ActionButton *actionButton;
		Vector3 *PositionOffset;
		Vector3 *LocalScale = Vector3::one;
		float MaxTimer = std::numeric_limits<float>::max();
		float Timer = 0.0f;
		bool effectCancellable = false;
	private:
		std::function<void()> OnClick;
		std::function<void()> OnMeetingEnds;
		std::function<bool(bool, RoleId)> HasButton;
		std::function<bool()> CouldUse;
		std::function<void()> OnEffectEnds;
	public:
		bool HasEffect = false;
		bool isEffectActive = false;
		bool showButtonText = true;
		std::wstring buttonText = L"";
		float EffectDuration = 0;
		Sprite *Sprite;
	private:
		HudManager *hudManager;
		bool mirror = false;
		std::optional<KeyCode*> hotkey;
		int joystickkey = 0;
		std::function<bool()> StopCountCool;
	public:
		virtual ~CustomButton()
		{
			delete actionButton;
			delete PositionOffset;
			delete LocalScale;
			delete Sprite;
			delete hudManager;
		}

		CustomButton(std::function<void()> OnClick, std::function<bool(bool, RoleId)> HasButton, std::function<bool()> CouldUse, std::function<void()> OnMeetingEnds, Sprite *Sprite, Vector3 *PositionOffset, HudManager *hudManager, ActionButton *textTemplate, std::optional<KeyCode*> &hotkey, int joystickkey, std::function<bool()> StopCountCool, bool HasEffect, float EffectDuration, std::function<void()> OnEffectEnds, bool mirror = false, const std::wstring &buttonText = L"");
		CustomButton(std::function<void()> OnClick, std::function<bool(bool, RoleId)> HasButton, std::function<bool()> CouldUse, std::function<void()> OnMeetingEnds, Sprite Sprite, Vector3 PositionOffset, HudManager hudManager, ActionButton textTemplate, std::optional<KeyCode*> hotkey, int joystickkey, std::function<bool()> StopCountCool, bool mirror = false, std::wstring buttonText = L"") : this(OnClick, HasButton, CouldUse, OnMeetingEnds, Sprite, PositionOffset, hudManager, textTemplate, hotkey, joystickkey, StopCountCool, false, 0.0f, [&] ()
		{
		}, mirror, buttonText) { } void onClickEvent(){if ((Timer <= 0.0f || (HasEffect && isEffectActive && effectCancellable)) && CouldUse()){actionButton->graphic->color = new Color(1.0f, 1.0f, 1.0f, 0.3f);
				OnClick();
	};
}

	public:
		static void HudUpdate();

		static void MeetingEndedUpdate();

		void setActive(bool isActive);

	private:
		void Update(bool isAlive, RoleId role);
	}

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [HarmonyPatch(typeof(HudManager), nameof(HudManager.Update))] class HudManagerUpdatePatch
	class HudManagerUpdatePatch
	{
	private:
		static void Postfix(HudManager *__instance);
	};
}
