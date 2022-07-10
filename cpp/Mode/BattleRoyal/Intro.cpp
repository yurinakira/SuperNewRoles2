#include "Intro.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../../TranslateDate.h"

using namespace UnityEngine;

namespace SuperNewRoles::Mode::BattleRoyal
{

	Il2CppSystem::Collections::Generic::List<PlayerControl*> *Intro::ModeHandler(IntroCutscene *__instance)
	{
		Il2CppSystem::Collections::Generic::List<PlayerControl*> *Teams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
		Teams->Add(PlayerControl::LocalPlayer);
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isImpostor(p) && p->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
			{
				Teams->Add(p);
			}
		}

//C# TO C++ CONVERTER TODO TASK: A 'delete Teams' statement was not added since Teams was used in a 'return' or 'throw' statement.
		return Teams;
	}

	void Intro::IntroHandler(IntroCutscene *__instance)
	{
		__instance->BackgroundBar.material->color = Color::white;
		__instance->TeamTitle->text = ModTranslation::getString(L"BattleRoyalModeName");
		__instance->TeamTitle->color = new Color32(116, 80, 48, std::numeric_limits<unsigned char>::max());
		__instance->ImpostorText->text = L"";
	}
}
