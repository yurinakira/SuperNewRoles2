#include "SelfBomber.h"
#include "../Buttons/Buttons.h"
#include "../ModHelpers.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"
#include "../CustomRPC/CustomRPC.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void SelfBomber::EndMeeting()
	{
		HudManagerStartPatch::SelfBomberButton->MaxTimer = PlayerControl::GameOptions::KillCooldown;
		HudManagerStartPatch::SelfBomberButton->Timer = PlayerControl::GameOptions::KillCooldown;
	}

	void SelfBomber::ResetCoolDown()
	{
		HudManagerStartPatch::SelfBomberButton->MaxTimer = PlayerControl::GameOptions::KillCooldown;
		HudManagerStartPatch::SelfBomberButton->Timer = PlayerControl::GameOptions::KillCooldown;
	}

	bool SelfBomber::isSelfBomber(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::SelfBomber::SelfBomberPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SelfBomber::SelfBomb()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && p->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
			{
				if (GetIsBomb(PlayerControl::LocalPlayer, p))
				{

					CustomRPC::RPCProcedure::ByBomKillRPC(CachedPlayer::LocalPlayer->PlayerId, p->PlayerId);

					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ByBomKillRPC), Hazel::SendOption::Reliable, -1);
					Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
					Writer->Write(p->PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
				}
			}
		}
		CustomRPC::RPCProcedure::BomKillRPC(CachedPlayer::LocalPlayer->PlayerId);
		MessageWriter *Writer2 = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::BomKillRPC), Hazel::SendOption::Reliable, -1);
		Writer2->Write(CachedPlayer::LocalPlayer->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(Writer2);
	}

	bool SelfBomber::GetIsBomb(PlayerControl *source, PlayerControl *player)
	{
		Vector3 *position = source->transform.position;
		Vector3 *playerposition = player->transform.position;
		auto r = CustomOption::CustomOptions::SelfBomberScope->getFloat();
		if ((position->x + r >= playerposition->x) && (playerposition->x >= position->x - r))
		{
			if ((position->y + r >= playerposition->y) && (playerposition->y >= position->y - r))
			{
				if ((position->z + r >= playerposition->z) && (playerposition->z >= position->z - r))
				{
					return true;
				}
			}
		}
		return false;
	}
}
