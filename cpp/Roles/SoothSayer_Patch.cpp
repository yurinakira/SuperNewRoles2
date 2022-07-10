//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "SoothSayer_Patch.h"
#include "../CustomRPC/CustomRPC.h"
#include "../ModHelpers.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../Intro/IntroDate.h"
#include "../TranslateDate.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Helpers/CachedPlayer.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void SoothSayer_updatepatch::Postfix(MeetingHud *__instance)
	{
		if (PlayerControl::LocalPlayer::isDead() && PlayerControl::LocalPlayer::isRole(RoleId::SoothSayer))
		{
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"SoothSayerButton") != nullptr)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"SoothSayerButton").gameObject);
				}
			});
		}
	}

std::wstring SoothSayer_Patch::namedate;

	void SoothSayer_Patch::SoothSayerOnClick(int Index, MeetingHud *__instance)
	{
		auto Target = ModHelpers::playerById(static_cast<unsigned char>(__instance->playerStates[Index].TargetPlayerId));
		auto introdate = SuperNewRoles::RoleHelpers::getRole(Target);
		if (RoleClass::SoothSayer::DisplayMode)
		{
			if (SuperNewRoles::RoleHelpers::isImpostor(Target))
			{
				namedate = L"Impostor";
			}
			if (SuperNewRoles::RoleHelpers::isHauntedWolf(Target))
			{
				namedate = L"Impostor";
			}
			else if (SuperNewRoles::RoleHelpers::isNeutral(Target))
			{
				namedate = L"Neutral";
			}
			else if (SuperNewRoles::RoleHelpers::isCrew(Target))
			{
				namedate = L"CrewMate";
			}
		}
		else
		{
			namedate = Intro::IntroDate::GetIntroDate(introdate, Target)->NameKey;
		}
		auto name = ModTranslation::getString(namedate + L"Name");
		FastDestroyableSingleton<HudManager*>::getInstance().Chat::AddChat(PlayerControl::LocalPlayer, std::wstring::Format(ModTranslation::getString(L"SoothSayerGetChat"), SuperNewRoles::ModHelpers::nameText(Target)->text, name));

		RoleClass::SoothSayer::Count--;
		if (!std::find(RoleClass::SoothSayer::DisplayedPlayer.begin(), RoleClass::SoothSayer::DisplayedPlayer.end(), Target->PlayerId) != RoleClass::SoothSayer::DisplayedPlayer.end())
		{
			RoleClass::SoothSayer::DisplayedPlayer.push_back(Target->PlayerId);
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"SoothSayerButton") != nullptr && x->TargetPlayerId == Target->PlayerId)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"SoothSayerButton").gameObject);
				}
			});
		}
		if (RoleClass::SoothSayer::Count <= 0)
		{
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"SoothSayerButton") != nullptr)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"SoothSayerButton").gameObject);
				}
			});
		}
	}

	void SoothSayer_Patch::Event(MeetingHud *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::SoothSayer) && PlayerControl::LocalPlayer::isAlive() && RoleClass::SoothSayer::Count >= 1)
		{
			for (int i = 0; i < __instance->playerStates->Length; i++)
			{
				PlayerVoteArea *playerVoteArea = __instance->playerStates[i];
				auto player = ModHelpers::playerById(static_cast<unsigned char>(__instance->playerStates[i].TargetPlayerId));
				if (SuperNewRoles::RoleHelpers::isAlive(player) && !std::find(RoleClass::SoothSayer::DisplayedPlayer.begin(), RoleClass::SoothSayer::DisplayedPlayer.end(), player->PlayerId) != RoleClass::SoothSayer::DisplayedPlayer.end() && player->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
				{
					GameObject *template_Keyword = playerVoteArea->Buttons.transform.Find(L"CancelButton")->gameObject;
					GameObject *targetBox = UnityEngine::Object::Instantiate(template_Keyword, playerVoteArea->transform);

					targetBox->name = L"SoothSayerButton";
					targetBox->transform->localPosition = new Vector3(1.0f, 0.03f, -1.0f);
					SpriteRenderer *renderer = targetBox->GetComponent<SpriteRenderer*>();
					renderer->sprite = RoleClass::SoothSayer::getButtonSprite();
					PassiveButton *button = targetBox->GetComponent<PassiveButton*>();
					button->OnClick.RemoveAllListeners();
					int copiedIndex = i;
					button->OnClick.AddListener(static_cast<UnityEngine::Events::UnityAction*>([&] ()
					{
						SoothSayerOnClick(copiedIndex, __instance);
					}));
				}
			}
		}
	}

	void SoothSayer_Patch::SpiritOnClick(int Index, MeetingHud *__instance)
	{
		auto Target = ModHelpers::playerById(static_cast<unsigned char>(__instance->playerStates[Index].TargetPlayerId));
		auto introdate = SuperNewRoles::RoleHelpers::getRole(Target);
		namedate = Intro::IntroDate::GetIntroDate(introdate, Target)->NameKey;
		if (RoleClass::SpiritMedium::DisplayMode)
		{
			if (SuperNewRoles::RoleHelpers::isImpostor(Target))
			{
				namedate = L"Impostor";
			}
			if (SuperNewRoles::RoleHelpers::isHauntedWolf(Target))
			{
				namedate = L"Impostor";
			}
			else if (SuperNewRoles::RoleHelpers::isNeutral(Target))
			{
				namedate = L"Neutral";
			}
			else if (SuperNewRoles::RoleHelpers::isCrew(Target))
			{
				namedate = L"CrewMate";
			}
		}
		else
		{
			namedate = Intro::IntroDate::GetIntroDate(introdate, Target)->NameKey;
		}
		auto name = ModTranslation::getString(namedate + L"Name");
		FastDestroyableSingleton<HudManager*>::getInstance().Chat::AddChat(PlayerControl::LocalPlayer, std::wstring::Format(ModTranslation::getString(L"SoothSayerGetChat"), SuperNewRoles::ModHelpers::nameText(Target)->text, name));
		RoleClass::SpiritMedium::MaxCount--;
		if (!std::find(RoleClass::SoothSayer::DisplayedPlayer.begin(), RoleClass::SoothSayer::DisplayedPlayer.end(), Target->PlayerId) != RoleClass::SoothSayer::DisplayedPlayer.end())
		{
			RoleClass::SoothSayer::DisplayedPlayer.push_back(Target->PlayerId);
		}
		if (RoleClass::SpiritMedium::MaxCount <= 0)
		{
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"SoothSayerButton") != nullptr && x->TargetPlayerId == Target->PlayerId)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"SoothSayerButton").gameObject);
				}
			});
			__instance->playerStates.ToList()->ForEach([&] (std::any x)
			{
				if (x::transform::FindChild(L"SoothSayerButton") != nullptr)
				{
					UnityEngine::Object::Destroy(x::transform::FindChild(L"SoothSayerButton").gameObject);
				}
			});
		}
	}

	void SoothSayer_Patch::spiritEvent(MeetingHud *__instance)
	{
		if (PlayerControl::LocalPlayer::isRole(RoleId::SpiritMedium) && PlayerControl::LocalPlayer::isAlive() && RoleClass::SpiritMedium::MaxCount >= 1)
		{
			for (int i = 0; i < __instance->playerStates->Length; i++)
			{
				PlayerVoteArea *playerVoteArea = __instance->playerStates[i];

				auto player = ModHelpers::playerById(static_cast<unsigned char>(__instance->playerStates[i].TargetPlayerId));
				if (!player->Data->Disconnected && SuperNewRoles::RoleHelpers::isDead(player) && !std::find(RoleClass::SoothSayer::DisplayedPlayer.begin(), RoleClass::SoothSayer::DisplayedPlayer.end(), player->PlayerId) != RoleClass::SoothSayer::DisplayedPlayer.end() && player->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
				{
					GameObject *template_Keyword = playerVoteArea->Buttons.transform.Find(L"CancelButton")->gameObject;
					GameObject *targetBox = UnityEngine::Object::Instantiate(template_Keyword, playerVoteArea->transform);

					targetBox->name = L"SoothSayerButton";
					targetBox->transform->localPosition = new Vector3(1.0f, 0.03f, -1.0f);
					SpriteRenderer *renderer = targetBox->GetComponent<SpriteRenderer*>();
					renderer->sprite = RoleClass::SoothSayer::getButtonSprite();
					PassiveButton *button = targetBox->GetComponent<PassiveButton*>();
					button->OnClick.RemoveAllListeners();

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
