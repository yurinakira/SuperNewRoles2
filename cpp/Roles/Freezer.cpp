#include "Freezer.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "../ModHelpers.h"
#include "../Mode/ModeHandler.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Freezer::ResetCoolDown()
	{
		HudManagerStartPatch::FreezerButton->MaxTimer = RoleClass::Freezer::CoolTime;
		HudManagerStartPatch::FreezerButton->Timer = HudManagerStartPatch::FreezerButton->MaxTimer;
		HudManagerStartPatch::FreezerButton->actionButton->cooldownTimerText->color = Color::white;
	}

	void Freezer::DownStart()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedFreeze), SendOption::Reliable, -1);
		writer->Write(true);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedFreeze(true);
	}

	void Freezer::ResetSpeed()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedFreeze), SendOption::Reliable, -1);
		writer->Write(false);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedFreeze(false);
	}

	void Freezer::SpeedDownEnd()
	{
		ResetSpeed();
		Freezer::ResetCoolDown();
	}

	bool Freezer::IsFreezer(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Freezer::FreezerPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Freezer::EndMeeting()
	{
		Freezer::ResetCoolDown();
		ResetSpeed();
	}

	void PlayerPhysicsSpeedPatch2::Postfix(PlayerPhysics *__instance)
	{
		if (AmongUsClient::Instance->GameState != AmongUsClient::GameStates::Started)
		{
			return;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (RoleClass::Freezer::IsSpeedDown)
			{
				__instance->body->velocity = new Vector2(0.0f, 0.0f);
			}
		}
	}

	void HudManagerUpdatePatch2::Postfix()
	{
		if (HudManagerStartPatch::FreezerButton->Timer <= 0.1f && RoleClass::Freezer::IsSpeedDown)
		{
			Freezer::SpeedDownEnd();
		}
	}
}
