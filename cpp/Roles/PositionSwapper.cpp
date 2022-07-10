#include "PositionSwapper.h"
#include "../Buttons/Buttons.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"
#include "../Main.h"
#include "../ModHelpers.h"
#include "../CustomRPC/CustomRPC.h"

using namespace Hazel;
using namespace SuperNewRoles::Buttons;
using namespace UnityEngine;

namespace SuperNewRoles::Roles
{

	void PositionSwapper::ResetCoolDown()
	{
		HudManagerStartPatch::PositionSwapperButton->MaxTimer = RoleClass::PositionSwapper::CoolTime;
		HudManagerStartPatch::PositionSwapperButton->Timer = RoleClass::PositionSwapper::CoolTime;
		RoleClass::PositionSwapper::ButtonTimer = DateTime::Now;
	}

	void PositionSwapper::EndMeeting()
	{
		ResetCoolDown();
	}

	void PositionSwapper::SwapStart()
	{
		std::vector<PlayerControl*> AlivePlayer;
		AlivePlayer.clear();
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (SuperNewRoles::RoleHelpers::isAlive(p) && p->CanMove && !SuperNewRoles::RoleHelpers::isImpostor(p))
			{
				AlivePlayer.push_back(p);
			}
			SuperNewRolesPlugin::Logger->LogInfo(L"ポジションスワップ:" + p->PlayerId + L"\n生存:" + StringHelper::toString(SuperNewRoles::RoleHelpers::isAlive(p)));
		}
		auto RandomPlayer = ModHelpers::GetRandom<PlayerControl*>(AlivePlayer);
		auto PushSwapper = PlayerControl::LocalPlayer;
		CustomRPC::RPCProcedure::PositionSwapperTP(RandomPlayer->PlayerId, PushSwapper->PlayerId);

		MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::PositionSwapperTP), Hazel::SendOption::Reliable, -1);
		Writer->Write(RandomPlayer->PlayerId);
		Writer->Write(PushSwapper->PlayerId);
		AmongUsClient::Instance->FinishRpcImmediately(Writer);
		//SuperNewRolesPlugin.Logger.LogInfo("ポジションスワップ:"+RandomPlayer.PlayerId+"\n生存:"+!RandomPlayer.isDead());
	}
}
