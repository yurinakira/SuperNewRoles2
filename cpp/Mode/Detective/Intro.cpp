#include "Intro.h"
#include "../../Helpers/CachedPlayer.h"
#include "main.h"
#include "../../TranslateDate.h"

namespace SuperNewRoles::Mode::Detective
{

	void Intro::YouAreHandle(IntroCutscene *__instance)
	{
		if (main::DetectivePlayer->PlayerId == CachedPlayer::LocalPlayer->PlayerId)
		{
			__instance->YouAreText->color = main::DetectiveColor;
			__instance->RoleText->text = ModTranslation::getString(L"DetectiveName");
			__instance->RoleText->color = main::DetectiveColor;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"DetectiveTitle1");
			__instance->RoleBlurbText->color = main::DetectiveColor;
		}
	}
}
