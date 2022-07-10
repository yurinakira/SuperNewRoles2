#include "EvilSpeedBooster.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "../ModHelpers.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{

	void EvilSpeedBooster::ResetCoolDown()
	{
		HudManagerStartPatch::EvilSpeedBoosterBoostButton->MaxTimer = RoleClass::EvilSpeedBooster::CoolTime;
		RoleClass::EvilSpeedBooster::ButtonTimer = DateTime::Now;
	}

	void EvilSpeedBooster::BoostStart()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedBoost), Hazel::SendOption::Reliable, -1);
		writer->Write(true);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedBoost(true, CachedPlayer::LocalPlayer->PlayerId);
		RoleClass::EvilSpeedBooster::IsSpeedBoost = true;
		EvilSpeedBooster::ResetCoolDown();
	}

	void EvilSpeedBooster::ResetSpeed()
	{
		MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetSpeedBoost), Hazel::SendOption::Reliable, -1);
		writer->Write(false);
		writer->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(writer);
		CustomRPC::RPCProcedure::SetSpeedBoost(false, CachedPlayer::LocalPlayer->PlayerId);
		RoleClass::EvilSpeedBooster::IsSpeedBoost = false;
	}

	void EvilSpeedBooster::SpeedBoostCheck()
	{
		if (!RoleClass::EvilSpeedBooster::IsSpeedBoost)
		{
			return;
		}
		if (HudManagerStartPatch::EvilSpeedBoosterBoostButton->Timer + RoleClass::EvilSpeedBooster::DurationTime <= RoleClass::EvilSpeedBooster::CoolTime)
		{
			SpeedBoostEnd();
		}
	}

	void EvilSpeedBooster::SpeedBoostEnd()
	{
		ResetSpeed();
		ResetCoolDown();
	}

	bool EvilSpeedBooster::IsEvilSpeedBooster(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::EvilSpeedBooster::EvilSpeedBoosterPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void EvilSpeedBooster::EndMeeting()
	{

		HudManagerStartPatch::EvilSpeedBoosterBoostButton->MaxTimer = RoleClass::EvilSpeedBooster::CoolTime;
		RoleClass::EvilSpeedBooster::ButtonTimer = DateTime::Now;
		ResetSpeed();

	}
}
