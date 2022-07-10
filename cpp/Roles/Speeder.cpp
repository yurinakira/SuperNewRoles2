#include "Speeder.h"
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

	void Speeder::ResetCoolDown()
	{
		HudManagerStartPatch::SpeederButton->MaxTimer = RoleClass::Speeder::CoolTime;
		HudManagerStartPatch::SpeederButton->Timer = HudManagerStartPatch::SpeederButton->MaxTimer;
		HudManagerStartPatch::SpeederButton->actionButton->cooldownTimerText->color = Color::white;
	}

	void Speeder::DownStart()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedDown), SendOption::Reliable, -1);
		writer->Write(true);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedDown(true);
	}

	void Speeder::ResetSpeed()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedDown), SendOption::Reliable, -1);
		writer->Write(false);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedDown(false);
	}

	void Speeder::SpeedDownEnd()
	{
		ResetSpeed();
		Speeder::ResetCoolDown();
	}

	bool Speeder::IsSpeeder(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Speeder::SpeederPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Speeder::EndMeeting()
	{
		Speeder::ResetCoolDown();
		ResetSpeed();
	}

	void PlayerPhysicsSpeedPatch::Postfix(PlayerPhysics *__instance)
	{
		if (AmongUsClient::Instance->GameState != AmongUsClient::GameStates::Started)
		{
			return;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (RoleClass::Speeder::IsSpeedDown)
			{
				__instance->body.velocity /= 10.0f;
			}
		}
	}

	void HudManagerUpdatePatch::Postfix()
	{
		if (HudManagerStartPatch::SpeederButton->Timer <= 0.1 && RoleClass::Speeder::IsSpeedDown)
		{
			Speeder::SpeedDownEnd();
		}
	}
}
