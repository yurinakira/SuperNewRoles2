#include "SabotageManager.h"
#include "Options.h"
#include "../Roles/RoleHelper.h"
#include "CognitiveDeficit/main.h"
#include "../Helpers/RPCHelper.h"
#include "../Helpers/CachedPlayer.h"

using namespace Hazel;
using namespace SuperNewRoles::Helpers;

namespace SuperNewRoles::Sabotage
{

SabotageManager::CustomSabotage SabotageManager::thisSabotage = static_cast<CustomSabotage>(0);
std::vector<ButtonBehavior*> SabotageManager::CustomButtons;

	bool SabotageManager::IsOK(CustomSabotage sabotage)
	{
		if (!Options::SabotageSetting->getBool())
		{
			return false;
		}
		switch (sabotage)
		{
			case CustomSabotage::CognitiveDeficit:
				if (PlayerControl::GameOptions::MapId != 4)
				{
					return false;
				}
				else
				{
					return Options::CognitiveDeficitSetting->getBool();
				}
		}
		return false;
	}

	bool SabotageManager::IsOKMeeting()
	{
		if (RoleHelpers::IsSabotage())
		{
			return false;
		}
		if (thisSabotage == CustomSabotage::None)
		{
			return true;
		}
		bool tempVar18;
		switch (thisSabotage)
		{
			case CustomSabotage::CognitiveDeficit:
				tempVar18 = CognitiveDeficit::main::IsLocalEnd;
				break;
			default:
				tempVar18 = false;
				break;
		}
		return tempVar18;
	}

InfectedOverlay *SabotageManager::InfectedOverlayInstance;

	void SabotageManager::SetSabotage(PlayerControl *player, CustomSabotage Sabotage, bool Is)
	{
		switch (Sabotage)
		{
			case CustomSabotage::CognitiveDeficit:
				if (Is)
				{
					CognitiveDeficit::main::StartSabotage();
				}
				else
				{
					CognitiveDeficit::main::EndSabotage(player);
				}
				break;
		}
	}

	void SabotageManager::ClearAndReloads()
	{
		InfectedOverlayInstance = nullptr;
		thisSabotage = CustomSabotage::None;
		CustomButtons = std::vector<ButtonBehavior*>();
		if (IsOK(CustomSabotage::CognitiveDeficit))
		{
			CognitiveDeficit::main::DefaultDistanceTime = Options::CognitiveDeficitReleaseTimeSetting->getFloat();
			CognitiveDeficit::main::DefaultUpdateTime = Options::CognitiveDeficitOutfitUpdateTimeSetting->getFloat();
			CognitiveDeficit::main::IsAllEndSabotage = Options::CognitiveDeficitIsAllEndSabotageSetting->getBool();
		}
	}

	void SabotageManager::Update()
	{
		if (CustomButtons.size() > 0)
		{
			if (InfectedOverlayInstance != nullptr)
			{
				float specialActive = (InfectedOverlayInstance->doors != nullptr && InfectedOverlayInstance->doors.IsActive) ? 1.0f : InfectedOverlayInstance->SabSystem.PercentCool;
				for (auto button : CustomButtons)
				{
					button->spriteRenderer.material.SetFloat(L"_Percent", specialActive);
				}
			}
			switch (thisSabotage)
			{
				case CustomSabotage::CognitiveDeficit:
					CognitiveDeficit::main::Update();
					break;
			}
		}
	}

	void SabotageManager::CustomSabotageRPC(PlayerControl *p, CustomSabotage type, bool Is)
	{
		MessageWriter *writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetCustomSabotage);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		writer->Write(static_cast<unsigned char>(type));
		writer->Write(Is);
		SuperNewRoles::Helpers::RPCHelper::EndRPC(writer);
		SetSabotage(p, type, Is);
	}
}
