#include "Jester.h"
#include "../../../CustomRPC/CustomRPC.h"
#include "../../../Patch/TaskCount.h"
#include "../../../Roles/RoleClass.h"
#include "../../../Helpers/RPCHelper.h"
#include "../../../EndGame/CustomEndReason.h"
#include "../Chat.h"
#include "../../../Patch/Chat.h"
#include "../../../Main.h"
#include "../../../Helpers/MapUtilities.h"
#include "../EndGameCheck.h"

using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

	void Jester::WrapUp(GameData::PlayerInfo *exiled)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (exiled->Object.isRole(CustomRPC::RoleId::Jester))
		{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(complate, all) = TaskCount.TaskDateNoClearCheck(exiled);
			auto [complate, all] = TaskCount::TaskDateNoClearCheck(exiled);
			if (!RoleClass::Jester::IsJesterTaskClearWin || complate >= all)
			{
				try
				{
					auto Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ShareWinner);
					Writer->Write(exiled->Object.PlayerId);
					SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
					CustomRPC::RPCProcedure::ShareWinner(exiled->Object.PlayerId);
					Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
					Writer->Write(static_cast<unsigned char>(CustomGameOverReason::JesterWin));
					SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
					CustomRPC::RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::JesterWin));
					auto winplayers = std::vector<PlayerControl*> {exiled->Object};
					//EndGameCheck.WinNeutral(winplayers);
					Chat::WinCond = CustomGameOverReason::JesterWin;
					Chat::Winner = {exiled->Object};
				}
				catch (const std::runtime_error &e)
				{
					SuperNewRolesPlugin::Logger->LogInfo(L"[SHR:Error] Jester WrapUp Error:" + e);
				}
				EndGameCheck::CustomEndGame(MapUtilities::CachedShipStatus, GameOverReason::HumansByVote, false);
			}
		}
		else if (exiled->Object.isRole(CustomRPC::RoleId::MadJester))
		{
//C# TO C++ CONVERTER NOTE: The following 'decomposition declaration' requires C++17:
//ORIGINAL LINE: var(complate, all) = TaskCount.TaskDateNoClearCheck(exiled);
			auto [complate, all] = TaskCount::TaskDateNoClearCheck(exiled);
			if (!RoleClass::MadJester::IsMadJesterTaskClearWin || complate >= all)
			{
				try
				{
					auto Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::ShareWinner);
					Writer->Write(exiled->Object.PlayerId);
					SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
					CustomRPC::RPCProcedure::ShareWinner(exiled->Object.PlayerId);
					Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
					Writer->Write(static_cast<unsigned char>(CustomGameOverReason::JesterWin));
					SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
					CustomRPC::RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::ImpostorWin));
					auto winplayers = std::vector<PlayerControl*> {exiled->Object};
					//EndGameCheck.WinNeutral(winplayers);
					Chat::WinCond = CustomGameOverReason::ImpostorWin;
					Chat::Winner = {exiled->Object};
				}
				catch (const std::runtime_error &e)
				{
					SuperNewRolesPlugin::Logger->LogInfo(L"[SHR:Error] Mad Jester WrapUp Error:" + e);
				}
				EndGameCheck::CustomEndGame(MapUtilities::CachedShipStatus, GameOverReason::ImpostorByVote, false);
			}
		}
	}
}
