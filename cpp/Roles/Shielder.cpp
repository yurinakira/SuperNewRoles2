#include "Shielder.h"
#include "../Buttons/Buttons.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleClass.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace SuperNewRoles::CustomRPC;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Shielder::HudManagerUpdatePatch::Postfix()
	{
		if (HudManagerStartPatch::ShielderButton->Timer <= 0.1f && RoleClass::Shielder::IsShield[CachedPlayer::LocalPlayer->PlayerId] && PlayerControl::LocalPlayer::isRole(RoleId::Shielder))
		{
			MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::SetShielder), SendOption::Reliable, -1);
			Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
			Writer->Write(false);
			AmongUsClient::Instance->FinishRpcImmediately(Writer);
			RPCProcedure::SetShielder(CachedPlayer::LocalPlayer->PlayerId, false);
			HudManagerStartPatch::ShielderButton->actionButton->cooldownTimerText->color = Color::white;
			HudManagerStartPatch::ShielderButton->MaxTimer = RoleClass::Shielder::CoolTime;
			HudManagerStartPatch::ShielderButton->Timer = HudManagerStartPatch::ShielderButton->MaxTimer;
		}
	}
}
