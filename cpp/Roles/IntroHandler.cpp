#include "IntroHandler.h"
#include "../LateTask.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleClass.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/Zombie/main.h"
#include "../Mode/BattleRoyal/main.h"
#include "../Mode/SuperHostRoles/FixedUpdate.h"
#include "../Mode/Werewolf/main.h"
#include "../Mode/CopsRobbers/main.h"

namespace SuperNewRoles::Roles
{

	void IntroHandler::Handler()
	{
		float time = 2.0f;
		if (PlayerControl::GameOptions::KillCooldown >= 10)
		{
			time = 7.0f;
		}
		new LateTask([&] ()
		{
			RoleClass::IsStart = true;
		}, time, L"IsStartOn");
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Pursuer))
		{
			RoleClass::Pursuer::arrow->arrow->SetActive(false);
			RoleClass::Pursuer::arrow->arrow->SetActive(true);
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::Zombie}))
		{
			Mode::Zombie::main::SetTimer();
		}
		else if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::BattleRoyal}))
		{
			Mode::BattleRoyal::main::IsCountOK = true;
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::SuperHostRoles}))
		{
			Mode::SuperHostRoles::FixedUpdate::SetRoleNames();
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::Werewolf}))
		{
			Mode::Werewolf::main::IntroHandler();
		}
		if (Mode::ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {Mode::ModeId::CopsRobbers}))
		{
			Mode::CopsRobbers::main::IsStart = true;
		}
	}
}
