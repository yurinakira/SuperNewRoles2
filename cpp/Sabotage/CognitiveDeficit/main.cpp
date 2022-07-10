//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "main.h"
#include "../../Main.h"
#include "../SabotageManager.h"
#include "../IconManager.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../ModHelpers.h"
#include "../../Roles/RoleHelper.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Patch/SetNames.h"
#include "../../OutfitManager.h"
#include "Patch.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomObject;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;
using namespace static UnityEngine::UI::Button;

namespace SuperNewRoles::Sabotage::CognitiveDeficit
{

	void main::StartSabotage()
	{
		IsLocalEnd = false;
		SuperNewRolesPlugin::Logger->LogInfo(L"スタートサボ！");
		SabotageManager::thisSabotage = SabotageManager::CustomSabotage::CognitiveDeficit;
		for (auto aw : ArrowDatas)
		{
			GameObject::Destroy(aw->arrow);
		}
		ArrowDatas = std::vector<Arrow*>();
		IsYellow = true;
		for (auto data : Datas)
		{
			Arrow *arrow = new Arrow(Color::yellow);
			arrow->arrow->SetActive(true);
			ArrowDatas.push_back(arrow);

//C# TO C++ CONVERTER TODO TASK: A 'delete arrow' statement was not added since arrow was passed to a method or constructor. Handle memory management manually.
		}
		UpdateTime = 0; // DefaultUpdateTime;
		DistanceTime = DefaultDistanceTime;
		ArrowUpdateColor = 0.25f;
		OKPlayers = std::vector<PlayerControl*>();
	}

float main::DefaultUpdateTime = 2;
float main::ArrowUpdateColor = 1;
float main::UpdateTime = 0;
float main::DistanceTime = 0;
float main::DefaultDistanceTime = 5;
bool main::IsYellow = false;
std::vector<Arrow*> main::ArrowDatas;
std::vector<Vector2*> main::Datas =
{
	new Vector2(-13.9f, -15.5f),
	new Vector2(-24.7f, -1.0f),
	new Vector2(10.6f, -15.5f)
};
std::vector<PlayerControl*> main::OKPlayers;
bool main::IsLocalEnd = false;
bool main::IsAllEndSabotage = false;

	void main::Create(InfectedOverlay *__instance)
	{
		if (SabotageManager::IsOK(SabotageManager::CustomSabotage::CognitiveDeficit))
		{
			ButtonBehavior *button = InfectedOverlay::Instantiate(__instance->allButtons[0], __instance->allButtons[0].transform.parent);
			button->transform.localPosition += new Vector3(0.2f, -1.7f, 0);
			button->spriteRenderer->sprite = IconManager::CognitiveDeficitgetButtonSprite();
			button->OnClick = new ButtonClickedEvent();

			button->OnClick.AddListener(static_cast<std::function<void()>>([&] ()
			{
				if (SabotageManager::InfectedOverlayInstance->CanUseSpecial)
				{
					SabotageManager::CustomSabotageRPC(PlayerControl::LocalPlayer, SabotageManager::CustomSabotage::CognitiveDeficit, true);
				}
			}));
			__instance->allButtons.AddItem(button);
			SabotageManager::CustomButtons.push_back(button);
		}
	}

	void main::Update()
	{
		if (SabotageManager::InfectedOverlayInstance != nullptr)
		{
			if (IsAllEndSabotage)
			{
				SabotageManager::InfectedOverlayInstance->SabSystem->Timer = SabotageManager::SabotageMaxTime;
			}
			else if (!IsLocalEnd)
			{
				SabotageManager::InfectedOverlayInstance->SabSystem->Timer = SabotageManager::SabotageMaxTime;
			}
		}
		bool IsOK = true;
		for (auto p3 : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p3) && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(OKPlayers, p3))
			{
				IsOK = false;
				if (PlayerControl::LocalPlayer::isImpostor())
				{
					if (!(SuperNewRoles::RoleHelpers::isImpostor(p3) || SuperNewRoles::RoleHelpers::isRole(p3, CustomRPC::RoleId::MadKiller)))
					{
						Color32 tempVar(18, 112, 214, std::numeric_limits<unsigned char>::max());
						SetNamesClass::SetPlayerNameColor(p3, &tempVar);
					}
				}
			}
		}
		if (IsOK)
		{
			SabotageManager::thisSabotage = SabotageManager::CustomSabotage::None;
			return;
		}
		if (!IsLocalEnd)
		{
			int arrowindex = 0;
			ArrowUpdateColor -= Time::fixedDeltaTime;
			std::optional<Color*> SetColor;
			if (ArrowUpdateColor <= 0)
			{
				if (IsYellow)
				{
					SetColor = Color::red;
					IsYellow = false;
				}
				else
				{
					SetColor = Color::yellow;
					IsYellow = true;
				}
				ArrowUpdateColor = 0.25f;
			}
			for (auto arrow : ArrowDatas)
			{
				arrow->Update(Datas[arrowindex], SetColor);
				arrowindex++;
			}
			bool IsOK2 = false;
			for (auto data : Datas)
			{
				if (!IsOK2)
				{
					if (Vector2::Distance(PlayerControl::LocalPlayer::GetTruePosition(), data) <= 1)
					{
						IsOK2 = true;
					}
				}
			}
			if (IsOK2)
			{
				DistanceTime -= Time::fixedDeltaTime;
				if (DistanceTime <= 0)
				{
					SabotageManager::CustomSabotageRPC(PlayerControl::LocalPlayer, SabotageManager::CustomSabotage::CognitiveDeficit, false);
				}
			}
			else
			{
				DistanceTime = DefaultDistanceTime;
			}
			UpdateTime -= Time::fixedDeltaTime;
			if (UpdateTime <= 0)
			{
				std::vector<PlayerControl*> target;
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (!p->Data->Disconnected && SuperNewRoles::RoleHelpers::isAlive(p))
					{
						target.push_back(p);
					}
				}
				for (auto p : CachedPlayer::AllPlayers)
				{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
