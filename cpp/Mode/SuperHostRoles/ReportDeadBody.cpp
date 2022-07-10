#include "ReportDeadBody.h"
#include "../../Roles/RoleClass.h"
#include "../../Patch/DeadPlayer.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Roles/RoleHelper.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles
{

	bool ReportDeadBody::ReportDeadBodyPatch(PlayerControl *__instance, GameData::PlayerInfo *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return true;
		}
		if (RoleClass::Assassin::TriggerPlayer != nullptr)
		{
			return false;
		}
		//会議ボタンでもレポートでも起こる処理

		if (target == nullptr)
		{
			//会議ボタンのみで起こる処理
			return true;
		};

		//死体レポートのみで起こる処理
		DeadPlayer *deadPlayer;
		deadPlayer = DeadPlayer::deadPlayers.empty() ? nullptr : (DeadPlayer::deadPlayers.Where([&] (std::any x)
		{
			if (x::player != nullptr)
			{
				x::player::PlayerId;
			}
		} == CachedPlayer::LocalPlayer->PlayerId)?.FirstOrDefault());
		//if (RoleClass.Bait.ReportedPlayer.Contains(target.PlayerId)) return true;
		if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::Minimalist))
		{
			auto a = RoleClass::Minimalist::UseReport;
			return a;
		}
		if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::Fox))
		{
			auto a = RoleClass::Fox::UseReport;
			return a;
		}
		//if (target.Object.isRole(CustomRPC.RoleId.Bait) && (!deadPlayer.killerIfExisting.isRole(CustomRPC.RoleId.Minimalist) || RoleClass.Minimalist.UseReport)) if (!RoleClass.Bait.ReportedPlayer.Contains(target.PlayerId)) { return false; } else { return true; }

		return true;
	}
}
