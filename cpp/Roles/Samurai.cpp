#include "Samurai.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleClass.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Buttons/Buttons.h"
#include "../ModHelpers.h"
#include "RoleHelper.h"
#include "../CustomOption/CustomOptionDate.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Samurai::MurderPatch::Postfix(PlayerControl *__instance)
	{
		if (CachedPlayer::LocalPlayer->PlayerId == __instance->PlayerId && PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Samurai))
		{
			PlayerControl::LocalPlayer::SetKillTimerUnchecked(RoleClass::Samurai::KillCoolTime);
		}
	}

	void Samurai::SetSamuraiButton()
	{
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Samurai))
		{
			if (!RoleClass::Samurai::UseVent)
			{
				FastDestroyableSingleton<HudManager*>::getInstance().ImpostorVentButton::gameObject::SetActive(false);
			}
			if (!RoleClass::Samurai::UseSabo)
			{
				FastDestroyableSingleton<HudManager*>::getInstance().SabotageButton::gameObject::SetActive(false);
			}
		}
	}

	void Samurai::FixedUpdate::Postfix()
	{
		SetSamuraiButton();
	}

	void Samurai::EndMeeting()
	{
		HudManagerStartPatch::SamuraiButton->MaxTimer = RoleClass::Samurai::SwordCoolTime;
		HudManagerStartPatch::SamuraiButton->Timer = RoleClass::Samurai::SwordCoolTime;
	}

	void Samurai::ResetCoolDown()
	{
		HudManagerStartPatch::SamuraiButton->MaxTimer = RoleClass::Samurai::SwordCoolTime;
		HudManagerStartPatch::SamuraiButton->Timer = RoleClass::Samurai::SwordCoolTime;
	}

	bool Samurai::isSamurai(PlayerControl *Player)
	{
		if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Samurai::SamuraiPlayer, Player))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Samurai::SamuraiKill()
	{
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && p->PlayerId != CachedPlayer::LocalPlayer->PlayerId)
			{
				if (Getsword(PlayerControl::LocalPlayer, p))
				{
					CustomRPC::RPCProcedure::BySamuraiKillRPC(CachedPlayer::LocalPlayer->PlayerId, p->PlayerId);
					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::BySamuraiKillRPC), Hazel::SendOption::Reliable, -1);
					Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
					Writer->Write(p->PlayerId);
					RoleClass::Samurai::Sword = true;
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
				}
			}
		}
	}

	bool Samurai::Getsword(PlayerControl *source, PlayerControl *player)
	{
		Vector3 *position = source->transform.position;
		Vector3 *playerposition = player->transform.position;
		auto r = CustomOption::CustomOptions::SamuraiScope->getFloat();
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

	void Samurai::IsSword()
	{
		RoleClass::Samurai::Sword = true;
	}
}
