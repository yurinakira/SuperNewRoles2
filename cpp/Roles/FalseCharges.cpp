#include "FalseCharges.h"
#include "../Mode/ModeHandler.h"
#include "../Helpers/CachedPlayer.h"
#include "RoleClass.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"
#include "../EndGame/CustomEndReason.h"
#include "../EndGame/EndGame.h"
#include "../ModHelpers.h"
#include "../Mode/SuperHostRoles/Chat.h"
#include "../Main.h"
#include "../Helpers/MapUtilities.h"
#include "../Mode/SuperHostRoles/EndGameCheck.h"

using namespace Hazel;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Roles
{

	void FalseCharges::WrapUp(PlayerControl *exiled)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (exiled != nullptr)
			{
				if (PlayerControl::LocalPlayer::isDead() && !CachedPlayer::LocalPlayer->Data->Disconnected && RoleClass::FalseCharges::Turns != 255)
				{
					if (RoleClass::FalseCharges::Turns <= 0)
					{
						return;
					}
					if (exiled->PlayerId == RoleClass::FalseCharges::FalseChargePlayer)
					{
						CustomRPC::RPCProcedure::ShareWinner(CachedPlayer::LocalPlayer->PlayerId);

						MessageWriter *Writer = RPCHelper::StartRPC(static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner));
						Writer->Write(CachedPlayer::LocalPlayer->PlayerId);
						SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
						if (AmongUsClient::Instance->AmHost)
						{
							CheckGameEndPatch::CustomEndGame(static_cast<GameOverReason*>(CustomGameOverReason::FalseChargesWin), false);
						}
						else
						{
							MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::CustomEndGame), SendOption::Reliable, -1);
							writer->Write(static_cast<unsigned char>(CustomGameOverReason::FalseChargesWin));
							writer->Write(false);
							AmongUsClient::Instance->FinishRpcImmediately(writer);
						}
					}
				}
			}
			RoleClass::FalseCharges::Turns--;
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			if (exiled != nullptr)
			{
				for (auto data : RoleClass::FalseCharges::FalseChargePlayers)
				{
					if (exiled->PlayerId == data.Value && !exiled->Data->Disconnected)
					{
						if (RoleClass::FalseCharges::AllTurns.find(data.Key) != RoleClass::FalseCharges::AllTurns.end() && RoleClass::FalseCharges::AllTurns[data.Key] > 0)
						{
							try
							{
								for (auto p : CachedPlayer::AllPlayers)
								{
									if (!p->Data->Disconnected && p->PlayerId != data.Key)
									{
										p->RpcMurderPlayer(p);
									}
								}
								auto player = ModHelpers::playerById(data.Key);
								auto Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ShareWinner);
								Writer->Write(player->PlayerId);
								SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
								CustomRPC::RPCProcedure::ShareWinner(player->PlayerId);
								Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
								Writer->Write(static_cast<unsigned char>(CustomGameOverReason::FalseChargesWin));
								SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
								CustomRPC::RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::FalseChargesWin));
								auto winplayers = std::vector<PlayerControl*> {player};
								//EndGameCheck.WinNeutral(winplayers);
								Chat::WinCond = CustomGameOverReason::FalseChargesWin;
								Chat::Winner = {player};
							}
							catch (const std::runtime_error &e)
							{
								SuperNewRolesPlugin::Logger->LogInfo(L"[SHR]冤罪師WrapUpエラー:" + e);
							}
							EndGameCheck::CustomEndGame(MapUtilities::CachedShipStatus, GameOverReason::HumansByVote, false);
						}
					}
				}
			}
			for (auto data : RoleClass::FalseCharges::AllTurns)
			{
				RoleClass::FalseCharges::AllTurns[data.Key]--;
			}
		}
	}
}
