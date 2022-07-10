#include "Nekomata.h"
#include "../Mode/ModeHandler.h"
#include "../ModHelpers.h"
#include "RoleClass.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleHelper.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Main.h"
#include "EvilEraser.h"
#include "../Patch/TaskCount.h"
#include "../EndGame/CustomEndReason.h"

using namespace Hazel;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

	void Nekomata::NekomataEnd(GameData::PlayerInfo *__instance)
	{
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			return;
		}
		if (__instance == nullptr)
		{
			return;
		}
		if (AmongUsClient::Instance->AmHost)
		{
			if ((__instance != nullptr && SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::NiceNekomata::NiceNekomataPlayer, __instance->Object)) || SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::EvilNekomata::EvilNekomataPlayer, __instance->Object) || SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::BlackCat::BlackCatPlayer, __instance->Object))
			{
				std::vector<PlayerControl*> p;
				for (auto p1 : CachedPlayer::AllPlayers)
				{
					if (p1->Data != __instance && SuperNewRoles::RoleHelpers::isAlive(p1))
					{
						p.push_back(p1);
					}
				}
				MessageWriter *RPCWriter = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ExiledRPC), Hazel::SendOption::Reliable, -1);
				RPCWriter->Write(__instance->PlayerId);
				AmongUsClient::Instance->FinishRpcImmediately(RPCWriter);
				CustomRPC::RPCProcedure::ExiledRPC(__instance->PlayerId);
				NekomataProc(p);
			}
		}
	}

	void Nekomata::NekomataProc(std::vector<PlayerControl*> &p)
	{
		auto rdm = ModHelpers::GetRandomIndex(p);
		auto random = p[rdm];
		SuperNewRolesPlugin::Logger->LogInfo(SuperNewRoles::ModHelpers::nameText(random)->text);
		if (EvilEraser::IsOKAndTryUse(EvilEraser::BlockTypes::NekomataExiled, random))
		{
			MessageWriter *RPCWriter = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::NekomataExiledRPC), Hazel::SendOption::Reliable, -1);
			RPCWriter->Write(random->PlayerId);
			AmongUsClient::Instance->FinishRpcImmediately(RPCWriter);
			CustomRPC::RPCProcedure::ExiledRPC(random->PlayerId);
			if ((SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::NiceNekomata::NiceNekomataPlayer, random) || SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::EvilNekomata::EvilNekomataPlayer, random) || SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::BlackCat::BlackCatPlayer, random)) && RoleClass::NiceNekomata::IsChain)
			{
				p.erase(p.begin() + rdm);
				NekomataProc(p);
			}
			if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(RoleClass::Jester::JesterPlayer, random))
			{
				if (!Roles->RoleClass.Jester::IsJesterTaskClearWin || (Roles->RoleClass.Jester::IsJesterTaskClearWin && std::get<1>(Patch::TaskCount::TaskDateNoClearCheck(random->Data)) - std::get<0>(Patch::TaskCount::TaskDateNoClearCheck(random->Data)) == 0))
				{
					CustomRPC::RPCProcedure::ShareWinner(random->PlayerId);
					MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), Hazel::SendOption::Reliable, -1);
					Writer->Write(random->PlayerId);
					AmongUsClient::Instance->FinishRpcImmediately(Writer);
					Roles->RoleClass.Jester::IsJesterWin = true;
					ShipStatus::RpcEndGame(static_cast<GameOverReason*>(CustomGameOverReason::JesterWin), false);
				}
			}
		}
	}
}
