#include "MurderPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "FixedUpdate.h"
#include "../../CustomRPC/CustomRPC.h"
#include "Helpers.h"
#include "../../LateTask.h"
#include "../../Roles/RoleClass.h"
#include "Roles/Bait.h"
#include "../../Roles/Bait.h"

using namespace Hazel;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void MurderPlayer::Postfix(PlayerControl *__instance, PlayerControl *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (SuperNewRoles::RoleHelpers::isAlive(target))
		{
			return;
		}
		FixedUpdate::SetRoleNames();
		if (SuperNewRoles::RoleHelpers::isRole(target, RoleId::Sheriff) || SuperNewRoles::RoleHelpers::isRole(target, RoleId::truelover) || SuperNewRoles::RoleHelpers::isRole(target, RoleId::MadMaker))
		{
			SuperNewRoles::Mode::SuperHostRoles::Helpers::RpcSetRoleDesync(target, RoleTypes::GuardianAngel);
		}
		if (SuperNewRoles::RoleHelpers::IsQuarreled(target))
		{
			if (AmongUsClient::Instance->AmHost)
			{
				auto Side = RoleHelpers::GetOneSideQuarreled(target);
				if (SuperNewRoles::RoleHelpers::isDead(Side))
				{
					new LateTask([&] ()
					{
						RPCProcedure::ShareWinner(target->PlayerId);
						MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
						Writer->Write(target->PlayerId);
						AmongUsClient::Instance->FinishRpcImmediately(Writer);
						Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
						Writer->Write(static_cast<unsigned char>(CustomGameOverReason::QuarreledWin));
						SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
						CustomRPC::RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::QuarreledWin));
						auto winplayers = std::vector<PlayerControl*> {target};
						//EndGameCheck.WinNeutral(winplayers);
						Chat::WinCond = CustomGameOverReason::QuarreledWin;
						Chat::Winner = {target};
						RoleClass::Quarreled::IsQuarreledWin = true;
						SuperHostRoles::EndGameCheck::CustomEndGame(MapUtilities::CachedShipStatus, GameOverReason::HumansByTask, false);
					}, 0.15f);
				}
			}
		}
		if (RoleClass::Lovers::SameDie && SuperNewRoles::RoleHelpers::IsLovers(target))
		{
			PlayerControl *Side = SuperNewRoles::RoleHelpers::GetOneSideLovers(target);
			if (SuperNewRoles::RoleHelpers::isAlive(Side))
			{
				Side->RpcMurderPlayer(Side);
			}
		}
		Roles->Bait::MurderPostfix(__instance, target);
		FixedUpdate::SetRoleName(target);
	}
}
