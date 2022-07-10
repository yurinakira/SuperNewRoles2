#include "Levelinger.h"
#include "../Helpers/CachedPlayer.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../Helpers/RPCHelper.h"
#include "../Patch/DeadPlayer.h"

using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

	void Levelinger::MurderPlayer(PlayerControl *__instance, PlayerControl *target)
	{
		if (__instance->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
		{
			return;
		}
		if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::Levelinger))
		{
			RoleClass::Levelinger::ThisXP += RoleClass::Levelinger::OneKillXP;
		}
		else if (SuperNewRoles::RoleHelpers::isRole(target, RoleId::Levelinger))
		{
			LevelingerRevive();
		}
	}

	void Levelinger::LevelingerRevive()
	{
		if (RoleClass::Levelinger::IsUseOKRevive)
		{
			if (RoleClass::Levelinger::ReviveUseXP <= RoleClass::Levelinger::ThisXP)
			{
				auto Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ReviveRPC);
				Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
				SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
				CustomRPC::RPCProcedure::ReviveRPC(CachedPlayer::LocalPlayer->PlayerId);
				Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::CleanBody);
				Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
				SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
				CustomRPC::RPCProcedure::CleanBody(CachedPlayer::LocalPlayer->PlayerId);
				CachedPlayer::LocalPlayer->Data->IsDead = false;
				if (!DeadPlayer::deadPlayers.empty())
				{
					DeadPlayer::deadPlayers.RemoveAll([&] (std::any x)
					{
						if (x::player != nullptr)
						{
							x::player::PlayerId;
						}
					} == CachedPlayer::LocalPlayer->PlayerId);
				}
				DeadPlayer::deadPlayers.RemoveAll([&] (std::any x)
				{
					if (x::player != nullptr)
					{
						x::player::PlayerId;
					}
				} == CachedPlayer::LocalPlayer->PlayerId);
				RoleClass::Levelinger::ThisXP -= RoleClass::Levelinger::ReviveUseXP;
			}
		}
	}
}
