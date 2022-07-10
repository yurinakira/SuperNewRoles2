#include "RedRidingHood.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../Patch/DeadPlayer.h"
#include "RoleHelper.h"
#include "EvilEraser.h"
#include "../Helpers/RPCHelper.h"

using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;

namespace SuperNewRoles::Roles
{

	void RedRidingHood::WrapUp(GameData::PlayerInfo *player)
	{
		if (PlayerControl::LocalPlayer::isDead() && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::NiceRedRidingHood))
		{
			if (RoleClass::NiceRedRidingHood::Count >= 1)
			{
				DeadPlayer *deadPlayer = DeadPlayer::deadPlayers.empty() ? nullptr : (DeadPlayer::deadPlayers.Where([&] (std::any x)
				{
					if (x::player != nullptr)
					{
						x::player::PlayerId;
					}
				} == CachedPlayer::LocalPlayer->PlayerId)?.FirstOrDefault());
				if (deadPlayer->killerIfExisting != nullptr && SuperNewRoles::RoleHelpers::isDead(deadPlayer->killerIfExisting))
				{
					if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::RedRidingHoodRevive, deadPlayer->killerIfExisting))
					{
						auto Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ReviveRPC);
						Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
						SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
						CustomRPC::RPCProcedure::ReviveRPC(CachedPlayer::LocalPlayer->PlayerId);
						Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::CleanBody);
						Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
						SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
						RoleClass::NiceRedRidingHood::deadbodypos = std::nullopt;
						CustomRPC::RPCProcedure::CleanBody(CachedPlayer::LocalPlayer->PlayerId);
						RoleClass::NiceRedRidingHood::Count--;
						CachedPlayer::LocalPlayer->Data->IsDead = false;

						RoleClass::NiceRedRidingHood::deadbodypos = std::nullopt;
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
					}
				}
			}
		}
	}
}
