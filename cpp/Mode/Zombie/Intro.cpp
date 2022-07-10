#include "Intro.h"
#include "../../Helpers/CachedPlayer.h"
#include "main.h"
#include "../../TranslateDate.h"

using namespace UnityEngine;

namespace SuperNewRoles::Mode::Zombie
{

	Il2CppSystem::Collections::Generic::List<PlayerControl*> *Intro::ModeHandler(IntroCutscene *__instance)
	{
		Il2CppSystem::Collections::Generic::List<PlayerControl*> *Teams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();

		if (PlayerControl::LocalPlayer::IsZombie())
		{
			Teams->Add(PlayerControl::LocalPlayer);
		}
		else
		{
			Teams->Add(PlayerControl::LocalPlayer);
			for (auto p : CachedPlayer::AllPlayers)
			{
				if (p->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
				{
					Teams->Add(p);
				}
			}
		}

//C# TO C++ CONVERTER TODO TASK: A 'delete Teams' statement was not added since Teams was used in a 'return' or 'throw' statement.
		return Teams;
	}

	void Intro::IntroHandler(IntroCutscene *__instance)
	{
		__instance->BackgroundBar.material->color = main::Zombiecolor;
		__instance->TeamTitle->text = ModTranslation::getString(L"ZombieModeName");
		__instance->TeamTitle->color = main::Zombiecolor;
		__instance->ImpostorText->text = L"";
	}

	void Intro::YouAreHandle(IntroCutscene *__instance)
	{
		Color *backcolor = main::Policecolor;
		std::wstring text = ModTranslation::getString(L"ZombiePoliceName");
		std::wstring desc = ModTranslation::getString(L"ZombiePoliceTitle1");
		if (PlayerControl::LocalPlayer::IsZombie())
		{
			text = ModTranslation::getString(L"ZombieZombieName");
			desc = ModTranslation::getString(L"ZombieZombieTitle1");
			backcolor = main::Zombiecolor;
		}
		__instance->YouAreText->color = backcolor;
		__instance->RoleText->text = text;
		__instance->RoleText->color = backcolor;
		__instance->RoleBlurbText->text = desc;
		__instance->RoleBlurbText->color = backcolor;
		/**
		if (PlayerControl.LocalPlayer.IsQuarreled())
		{
		    __instance.RoleBlurbText.text = __instance.RoleBlurbText.text + "\n" + ModHelpers.cs(RoleClass.Quarreled.color, String.Format(ModTranslation.getString("QuarreledIntro"), SetNamesClass.AllNames[PlayerControl.LocalPlayer.GetOneSideQuarreled().PlayerId]));
		}
		*/
	}
}
