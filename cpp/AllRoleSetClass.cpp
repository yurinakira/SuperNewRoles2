//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "AllRoleSetClass.h"
#include "Mode/ModeHandler.h"
#include "CustomOption/CustomOptionDate.h"
#include "Helpers/RPCHelper.h"
#include "Mode/SuperHostRoles/RoleSelectHandler.h"
#include "Helpers/CachedPlayer.h"
#include "BotManager.h"
#include "ModHelpers.h"
#include "Main.h"
#include "Mode/SuperHostRoles/FixedUpdate.h"
#include "Mode/BattleRoyal/main.h"
#include "Mode/CopsRobbers/RoleSelectHandler.h"
#include "Mode/Werewolf/RoleSelectHandler.h"
#include "Mode/NotImpostorCheck/SelectRolePatch.h"
#include "Mode/Detective/main.h"
#include "LateTask.h"
#include "CustomOption/CustomOptionModel.h"
#include "Roles/RoleHelper.h"
#include "ChacheManager/main.h"
#include "Intro/IntroDate.h"
#include "Roles/TeamRoleType.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles
{

bool RpcSetRoleReplacer::doReplace = false;
CustomRpcSender *RpcSetRoleReplacer::sender;
std::vector<(PlayerControl, RoleTypes)*> RpcSetRoleReplacer::StoragedData;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] RoleTypes roleType)
	bool RpcSetRoleReplacer::Prefix(PlayerControl *__instance, RoleTypes *roleType)
	{
		return true;
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return true;
		}
		if (doReplace && sender != nullptr)
		{
			StoragedData.push_back((__instance, roleType));
			return false;
		}
		else
		{
			return true;
		}
	}

	void RpcSetRoleReplacer::Release()
	{
		sender->StartMessage(-1);
		for (auto pair : StoragedData)
		{
			pair->Item1->SetRole(pair->Item2);
			sender->StartRpc(pair->Item1->NetId, RpcCalls::SetRole).Write(static_cast<unsigned short>(pair->Item2)).EndRpc();
		}
		sender->EndMessage();
		doReplace = false;
	}

	void RpcSetRoleReplacer::StartReplace(CustomRpcSender *sender)
	{
		RpcSetRoleReplacer::sender = sender;
		StoragedData = std::vector<(PlayerControl, RoleTypes)*>();
		doReplace = true;
	}

	void startgamepatch::Postfix()
	{
		SuperNewRoles::Helpers::RPCHelper::EndRPC(RPCHelper::StartRPC(CustomRPC::CustomRPC::StartGameRPC));
		CustomRPC::RPCProcedure::StartGameRPC();

		RoleSelectHandler::SpawnBots();
	}

bool RoleManagerSelectRolesPatch::IsNotPrefix = false;
bool RoleManagerSelectRolesPatch::IsRPCSetRoleOK = false;
bool RoleManagerSelectRolesPatch::IsSetRoleRpc = false;
bool RoleManagerSelectRolesPatch::IsShapeSet = false;
bool RoleManagerSelectRolesPatch::IsNotDesync = false;

	bool RoleManagerSelectRolesPatch::Prefix()
	{
		AllRoleSetClass::SetPlayerNum();
		IsNotPrefix = false;
		IsSetRoleRpc = false;
		IsRPCSetRoleOK = true;
		IsShapeSet = false;
		IsNotDesync = true;
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::NotImpostorCheck}))
		{
			IsNotDesync = false;
		}
		/*
		if (ModeHandler.isMode(ModeId.SuperHostRoles))
		{
		    IsNotDesync = false;
		}
		*/
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			CustomRpcSender *sender = CustomRpcSender::Create(L"SelectRoles Sender", SendOption::Reliable);
			std::vector<PlayerControl*> SelectPlayers;
			AllRoleSetClass::impostors = std::vector<PlayerControl*>();
			for (auto player : CachedPlayer::AllPlayers)
			{
				if (!player->Data->Disconnected && SuperNewRoles::BotManager::IsPlayer(player))
				{
					SelectPlayers.push_back(player);
				}
			}
			for (int i = 0; i < PlayerControl::GameOptions::NumImpostors; i++)
			{
				if (SelectPlayers.size() >= 1)
				{
					auto newimpostor = ModHelpers::GetRandom(SelectPlayers);
					AllRoleSetClass::impostors.push_back(newimpostor);
					newimpostor->Data->Role->Role = RoleTypes::Impostor;
					newimpostor->Data->Role->TeamType = RoleTeamTypes::Impostor;
					SelectPlayers.RemoveAll([&] (std::any a)
					{
						return a->PlayerId == newimpostor->PlayerId;
					});
				}
			}
			sender = RoleSelectHandler::RoleSelect(sender);

			for (auto player : AllRoleSetClass::impostors)
			{
				SuperNewRoles::CustomRpcSenderExtensions::RpcSetRole(sender, player, RoleTypes::Impostor);
			}
			for (auto player : CachedPlayer::AllPlayers)
			{
				if (!player->Data->Disconnected && !SuperNewRoles::ModHelpers::IsCheckListPlayerControl(AllRoleSetClass::impostors, player))
				{
					SuperNewRoles::CustomRpcSenderExtensions::RpcSetRole(sender, player, RoleTypes::Crewmate);
				}
			}

			//サーバーの役職判定をだます
			for (auto pc : PlayerControl::AllPlayerControls)
			{
				sender->AutoStartRpc(pc->NetId, static_cast<unsigned char>(RpcCalls::SetRole))->Write(static_cast<unsigned short>(RoleTypes::Shapeshifter))->EndRpc();
			}
			//RpcSetRoleReplacerの送信処理
			sender->SendMessage();

			try
			{
				AllRoleSetClass::QuarreledRandomSelect();
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"RoleSelectError:" + e);
			}

			try
			{
				AllRoleSetClass::LoversRandomSelect();
			}
			catch (const std::runtime_error &e)
			{
				SuperNewRolesPlugin::Logger->LogInfo(L"RoleSelectError:" + e);
			}
			FixedUpdate::SetRoleNames();
			return false;
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}))
		{
			Mode::BattleRoyal::main::ChangeRole::Postfix();
			return false;
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers}))
		{
			Mode::CopsRobbers::RoleSelectHandler::Handler();
			return false;
		}
		return true;
	}

	void RoleManagerSelectRolesPatch::Postfix()
	{
		IsSetRoleRpc = true;
		IsRPCSetRoleOK = false;
		IsNotPrefix = true;
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			AllRoleSetClass::AllRoleSet();
		}
		else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Werewolf}))
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
