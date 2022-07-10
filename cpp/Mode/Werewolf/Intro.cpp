#include "Intro.h"
#include "../../ModHelpers.h"
#include "main.h"
#include "../../TranslateDate.h"
#include "../../Roles/RoleClass.h"
#include "../../CustomRPC/CustomRPC.h"

using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::Werewolf
{

	void Intro::YouAreHandle(IntroCutscene *__instance)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(main::HunterPlayers, PlayerControl::LocalPlayer))
		{
			__instance->YouAreText->color = Color::green;
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfHunter");
			__instance->RoleText->color = Color::green;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfHunterText");
			__instance->RoleBlurbText->color = Color::green;
		}
		else if (PlayerControl::LocalPlayer::isImpostor())
		{
			__instance->YouAreText->color = RoleClass::ImpostorRed;
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfImpostor");
			__instance->RoleText->color = RoleClass::ImpostorRed;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfImpostorText");
			__instance->RoleBlurbText->color = RoleClass::ImpostorRed;
		}
		else if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::MadMate))
		{
			__instance->YouAreText->color = RoleClass::ImpostorRed;
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfMadmate");
			__instance->RoleText->color = RoleClass::ImpostorRed;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfMadmateText");
			__instance->RoleBlurbText->color = RoleClass::ImpostorRed;
		}
		else if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::DefaultRole))
		{
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfCrewmate");
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfCrewmateText");
		}
		else if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::SoothSayer))
		{
			__instance->YouAreText->color = RoleClass::SoothSayer::color;
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfFortuneTeller");
			__instance->RoleText->color = RoleClass::SoothSayer::color;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfFortuneTellerText");
			__instance->RoleBlurbText->color = RoleClass::SoothSayer::color;
		}
		else if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::SoothSayer))
		{
			__instance->YouAreText->color = RoleClass::SpiritMedium::color;
			__instance->RoleText->text = ModTranslation::getString(L"WareWolfMedium");
			__instance->RoleText->color = RoleClass::SpiritMedium::color;
			__instance->RoleBlurbText->text = ModTranslation::getString(L"WereWolfMediumText");
			__instance->RoleBlurbText->color = RoleClass::SpiritMedium::color;
		}
	}
}
