#include "Intro.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../BotManager.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Roles/RoleHelper.h"
#include "../../Main.h"
#include "../../Intro/IntroDate.h"
#include "../../TranslateDate.h"
#include "../../ModHelpers.h"
#include "../../Roles/RoleClass.h"

using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	Il2CppSystem::Collections::Generic::List<PlayerControl*> *Intro::ModeHandler(IntroCutscene *__instance)
	{
		Il2CppSystem::Collections::Generic::List<PlayerControl*> *Teams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
		Teams->Add(PlayerControl::LocalPlayer);
		try
		{
			if (PlayerControl::LocalPlayer::isCrew())
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (p->PlayerId != CachedPlayer::LocalPlayer->PlayerId && SuperNewRoles::BotManager::IsPlayer(p))
					{
						Teams->Add(p);
					}
				}
			}
			else if (PlayerControl::LocalPlayer::isImpostor())
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					if ((SuperNewRoles::RoleHelpers::isImpostor(p) || SuperNewRoles::RoleHelpers::isRole(p, CustomRPC::RoleId::Spy)) && p->PlayerId != CachedPlayer::LocalPlayer->PlayerId && SuperNewRoles::BotManager::IsPlayer(p))
					{
						Teams->Add(p);
					}
				}
			}
		}
		catch (const std::runtime_error &e)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"[SHR:Intro] Intro Error:" + e);
		}

//C# TO C++ CONVERTER TODO TASK: A 'delete Teams' statement was not added since Teams was used in a 'return' or 'throw' statement.
		return Teams;
	}

	void Intro::IntroHandler(IntroCutscene *__instance)
	{
		/*
		__instance.BackgroundBar.material.color = Color.white;
		__instance.TeamTitle.text = ModTranslation.getString("BattleRoyalModeName");
		__instance.TeamTitle.color = new Color32(116,80,48,byte.MaxValue);
		__instance.ImpostorText.text = "";
		*/
	}

	void Intro::RoleTextHandler(IntroCutscene *__instance)
	{
		auto myrole = PlayerControl::LocalPlayer::getRole();
//C# TO C++ CONVERTER TODO TASK: The following 'is' operator pattern is not converted by C# to C++ Converter:
		if (myrole is not (CustomRPC::RoleId::DefaultRole or CustomRPC::RoleId::Bestfalsecharge))
		{
			auto date = SuperNewRoles::Intro::IntroDate::GetIntroDate(myrole);
			__instance->YouAreText->color = date->color;
			__instance->RoleText->text = ModTranslation::getString(date->NameKey + L"Name");
			__instance->RoleText->color = date->color;
			__instance->RoleBlurbText->text = date->TitleDesc;
			__instance->RoleBlurbText->color = date->color;
		}
		if (PlayerControl::LocalPlayer::IsLovers())
		{
			__instance->RoleBlurbText.text += L"\n" + ModHelpers::cs(RoleClass::Lovers::color, std::wstring::Format(ModTranslation::getString(L"LoversIntro"), PlayerControl::LocalPlayer::GetOneSideLovers() == nullptr ? std::any() : (((PlayerControl::LocalPlayer::GetOneSideLovers().getDefaultName()) != nullptr) ? PlayerControl::LocalPlayer::GetOneSideLovers().getDefaultName() : L"")));
		}
		if (PlayerControl::LocalPlayer::IsQuarreled())
		{
			__instance->RoleBlurbText.text += L"\n" + ModHelpers::cs(RoleClass::Quarreled::color, std::wstring::Format(ModTranslation::getString(L"QuarreledIntro"), PlayerControl::LocalPlayer::GetOneSideQuarreled() == nullptr ? std::any() : (((PlayerControl::LocalPlayer::GetOneSideQuarreled()->Data == nullptr ? nullptr : PlayerControl::LocalPlayer::GetOneSideQuarreled().Data->PlayerName) != nullptr) ? (PlayerControl::LocalPlayer::GetOneSideQuarreled()->Data == nullptr ? nullptr : PlayerControl::LocalPlayer::GetOneSideQuarreled().Data->PlayerName) : L"")));
		}
		/**
	
		if (PlayerControl.LocalPlayer.IsQuarreled())
		{
		    __instance.RoleBlurbText.text = __instance.RoleBlurbText.text + "\n" + ModHelpers.cs(RoleClass.Quarreled.color, String.Format(ModTranslation.getString("QuarreledIntro"), SetNamesClass.AllNames[PlayerControl.LocalPlayer.GetOneSideQuarreled().PlayerId]));
		}
		*/
	}
}
