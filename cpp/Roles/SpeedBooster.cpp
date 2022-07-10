#include "SpeedBooster.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../ModHelpers.h"
#include "../Mode/ModeHandler.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

	void SpeedBooster::ResetCoolDown()
	{
		HudManagerStartPatch::SpeedBoosterBoostButton->MaxTimer = RoleClass::SpeedBooster::CoolTime;
		RoleClass::SpeedBooster::ButtonTimer = DateTime::Now;
	}

	void SpeedBooster::BoostStart()
	{
		RoleClass::SpeedBooster::IsSpeedBoost = true;
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedBoost), Hazel::SendOption::Reliable, -1);
		writer->Write(true);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedBoost(true, CachedPlayer::LocalPlayer->PlayerId);
		SpeedBooster::ResetCoolDown();
	}

	void SpeedBooster::ResetSpeed()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedBoost), Hazel::SendOption::Reliable, -1);
		writer->Write(false);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedBoost(false, CachedPlayer::LocalPlayer->PlayerId);
	}

	void SpeedBooster::SpeedBoostEnd()
	{
		ResetSpeed();
	}

	bool SpeedBooster::IsSpeedBooster(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::SpeedBooster::SpeedBoosterPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SpeedBooster::EndMeeting()
	{

		HudManagerStartPatch::SpeedBoosterBoostButton->MaxTimer = RoleClass::SpeedBooster::CoolTime;
		RoleClass::SpeedBooster::ButtonTimer = DateTime::Now;
		ResetSpeed();
	}

	void SpeedBooster::PlayerPhysicsSpeedPatch::Postfix(PlayerPhysics *__instance)
	{
		if (AmongUsClient::Instance->GameState != AmongUsClient::GameStates::Started)
		{
			return;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (__instance->AmOwner && __instance->myPlayer.isRole(CustomRPC::RoleId::SpeedBooster) && RoleClass::SpeedBooster::IsBoostPlayers.find(__instance->myPlayer.PlayerId) != RoleClass::SpeedBooster::IsBoostPlayers.end() && __instance->myPlayer.CanMove && GameData::Instance && RoleClass::SpeedBooster::IsBoostPlayers[__instance->myPlayer.PlayerId])
			{
				__instance->body->velocity = __instance->body.velocity * RoleClass::SpeedBooster::Speed;
			}
			else if (__instance->AmOwner && RoleClass::EvilSpeedBooster::IsBoostPlayers.find(__instance->myPlayer.PlayerId) != RoleClass::EvilSpeedBooster::IsBoostPlayers.end() && __instance->myPlayer.CanMove && GameData::Instance && RoleClass::EvilSpeedBooster::IsBoostPlayers[__instance->myPlayer.PlayerId])
			{
				__instance->body->velocity = __instance->body.velocity * RoleClass::EvilSpeedBooster::getSpeed();
			}
		}
	}
}
