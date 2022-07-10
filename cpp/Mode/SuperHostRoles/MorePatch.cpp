#include "MorePatch.h"
#include "FixedUpdate.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Roles/RoleClass.h"
#include "../../Roles/RoleHelper.h"
#include "../../Helpers/CachedPlayer.h"
#include "../BattleRoyal/main.h"
#include "../../LateTask.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	void MorePatch::PlayerControlCompleteTaskPatch::Postfix(PlayerControl *__instance)
	{
		FixedUpdate::SetRoleName(__instance);
	}

	bool MorePatch::RepairSystem(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount)
	{
		if (systemType == SystemTypes::Sabotage && AmongUsClient::Instance->GameMode != GameModes::FreePlay)
		{
			if ((SuperNewRoles::RoleHelpers::isRole(player, RoleId::Jackal) && !RoleClass::Jackal::IsUseSabo) || player->isRole(RoleId::Demon, RoleId::Arsonist, RoleId::RemoteSheriff, RoleId::Sheriff, RoleId::truelover, RoleId::FalseCharges, RoleId::MadMaker))
			{
				return false;
			}
			if (!RoleClass::Minimalist::UseSabo && SuperNewRoles::RoleHelpers::isRole(player, RoleId::Minimalist))
			{
				return false;
			}
			if (!RoleClass::Samurai::UseSabo && SuperNewRoles::RoleHelpers::isRole(player, RoleId::Samurai))
			{
				return false;
			}
			if (!RoleClass::Egoist::UseSabo && SuperNewRoles::RoleHelpers::isRole(player, RoleId::Egoist))
			{
				return false;
			}
		}
		if (PlayerControl::LocalPlayer::IsUseVent() && RoleHelpers::IsComms())
		{
			if (BattleRoyal::main::VentData.find(CachedPlayer::LocalPlayer->PlayerId) != BattleRoyal::main::VentData.end())
			{
				auto data = BattleRoyal::main::VentData[CachedPlayer::LocalPlayer->PlayerId];
				if (data != nullptr)
				{
					PlayerControl::LocalPlayer::MyPhysics::RpcExitVent(static_cast<int>(data));
				}
			}
		}
		return true;
	}

	void MorePatch::StartMeeting(MeetingHud *__instance)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		FixedUpdate::SetRoleNames(true);
		RoleClass::IsMeeting = true;
		new LateTask([&] ()
		{
			FixedUpdate::SetDefaultNames();
		}, 5.0f, L"SetMeetingName");
	}

	void MorePatch::MeetingEnd()
	{
	}
}
