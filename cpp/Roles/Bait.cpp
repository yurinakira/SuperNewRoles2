#include "Bait.h"
#include "../Main.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "../Patch/DeadPlayer.h"
#include "EvilEraser.h"
#include "../CustomRPC/CustomRPC.h"

using namespace Hazel;
using namespace SuperNewRoles::Patch;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void Bait::BaitUpdate::Postfix(PlayerControl *__instance)
	{
		SuperNewRolesPlugin::Logger->LogInfo(RoleClass::Bait::ReportTime);
		RoleClass::Bait::ReportTime -= Time::fixedDeltaTime;
		DeadPlayer *deadPlayer = DeadPlayer::deadPlayers.empty() ? nullptr : (DeadPlayer::deadPlayers.Where([&] (std::any x)
		{
			if (x::player != nullptr)
			{
				x::player::PlayerId;
			}
		} == CachedPlayer::LocalPlayer->PlayerId)?.FirstOrDefault());

		if (deadPlayer->killerIfExisting != nullptr && RoleClass::Bait::ReportTime <= 0.0f)
		{
			if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::BaitReport))
			{
				MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ReportDeadBody), Hazel::SendOption::Reliable, -1);
				writer->Write(deadPlayer->killerIfExisting->PlayerId);
				writer->Write(CachedPlayer::LocalPlayer->PlayerId);
				AmongUsClient::Instance->FinishRpcImmediately(writer);
				CustomRPC::RPCProcedure::ReportDeadBody(deadPlayer->killerIfExisting->PlayerId, CachedPlayer::LocalPlayer->PlayerId);
			}
			RoleClass::Bait::Reported = true;
		}
	}
}
