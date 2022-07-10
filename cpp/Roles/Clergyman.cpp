#include "Clergyman.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../ModHelpers.h"
#include "CountChanger.h"
#include "TeamRoleType.h"
#include "../CustomMsg.h"
#include "../TranslateDate.h"
#include "EvilEraser.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;

namespace SuperNewRoles::Roles
{

	void Clergyman::ResetCoolDown()
	{
		HudManagerStartPatch::ClergymanLightOutButton->MaxTimer = RoleClass::Clergyman::CoolTime;
		RoleClass::Clergyman::ButtonTimer = DateTime::Now;
	}

	bool Clergyman::isClergyman(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Clergyman::ClergymanPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Clergyman::LightOutStart()
	{
		MessageWriter *RPCWriter = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::RPCClergymanLightOut), Hazel::SendOption::Reliable, -1);
		RPCWriter->Write(true);
		AmongUsClient::Instance->FinishRpcImmediately(RPCWriter);
	}

	bool Clergyman::IsLightOutVision()
	{
		if (RoleClass::Clergyman::OldButtonTime <= 0)
		{
			return false;
		}
		if (CountChanger::GetRoleType(PlayerControl::LocalPlayer) == TeamRoleType::Impostor)
		{
			return true;
		}
		if (CountChanger::IsChangeMadmate(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadMayor(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadJester(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadStuntMan(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadHawk(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadSeer(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeMadMaker(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeJackal(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeSidekick(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeJackalFriends(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeSeerFriends(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeJackalSeer(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeSidekickSeer(PlayerControl::LocalPlayer))
		{
			return true;
		}
		if (CountChanger::IsChangeBlackCat(PlayerControl::LocalPlayer))
		{
			return true;
		}
		return false;
	}

	bool Clergyman::IsLightOutVisionNoTime()
	{
		if (CountChanger::GetRoleType(PlayerControl::LocalPlayer) == TeamRoleType::Impostor)
		{
			return true;
		}
		return false;
	}

	void Clergyman::LightOutStartRPC()
	{
		if (IsLightOutVisionNoTime())
		{
			new CustomMessage(ModTranslation::getString(L"ClergymanLightOutMessage"), RoleClass::Clergyman::DurationTime);
		}
		if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::ClergymanLightOut))
		{
			RoleClass::Clergyman::OldButtonTimer = DateTime::Now;
		}
	}

	void Clergyman::EndMeeting()
	{
		HudManagerStartPatch::ClergymanLightOutButton->MaxTimer = RoleClass::Clergyman::CoolTime;
		RoleClass::Clergyman::ButtonTimer = DateTime::Now;
		RoleClass::Clergyman::IsLightOff = false;
	}
}
