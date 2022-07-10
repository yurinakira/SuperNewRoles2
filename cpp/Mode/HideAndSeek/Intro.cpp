#include "Intro.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../TranslateDate.h"

using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{

	Il2CppSystem::Collections::Generic::List<PlayerControl*> *Intro::ModeHandler(IntroCutscene *__instance)
	{
		Il2CppSystem::Collections::Generic::List<PlayerControl*> *ImpostorTeams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
		int ImpostorNum = 0;
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (player->Data->Role.IsImpostor)
			{
				ImpostorNum++;
				ImpostorTeams->Add(player);
			}
		}

//C# TO C++ CONVERTER TODO TASK: A 'delete ImpostorTeams' statement was not added since ImpostorTeams was used in a 'return' or 'throw' statement.
		return ImpostorTeams;
	}

	void Intro::IntroHandler(IntroCutscene *__instance)
	{
		Il2CppSystem::Collections::Generic::List<PlayerControl*> *ImpostorTeams = new Il2CppSystem::Collections::Generic->List<PlayerControl*>();
		int ImpostorNum = 0;
		for (auto player : CachedPlayer::AllPlayers)
		{
			if (player->Data->Role.IsImpostor)
			{
				ImpostorNum++;
				ImpostorTeams->Add(player);
			}
		}
		__instance->BackgroundBar.material->color = Color::white;
		__instance->TeamTitle->text = ModTranslation::getString(L"HideAndSeekModeName");
		__instance->TeamTitle->color = Color::yellow;
		__instance->ImpostorText->text = StringHelper::formatSimple(L"この{0}人が鬼だ。", std::to_wstring(ImpostorNum));
		__instance->ImpostorText->color = Color::yellow;

		delete ImpostorTeams;
	}
}
