//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "RoleSelectHandler.h"
#include "../../Main.h"
#include "../../AllRoleSetClass.h"
#include "SyncSetting.h"
#include "../../ChacheManager/main.h"
#include "main.h"
#include "../ModeHandler.h"
#include "../../CustomOption/CustomOptionDate.h"
#include "../../BotManager.h"
#include "../../TranslateDate.h"
#include "../../Roles/RoleClass.h"
#include "../../PlayerControlHepler.h"
#include "../../ModHelpers.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Intro/IntroDate.h"
#include "../../Roles/TeamRoleType.h"

using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

SuperNewRoles::CustomRpcSender *RoleSelectHandler::sender = nullptr;

	SuperNewRoles::CustomRpcSender *RoleSelectHandler::RoleSelect(CustomRpcSender *send)
	{
		sender = send;
		SuperNewRolesPlugin::Logger->LogInfo(L"[SHR] ROLESELECT");
		if (!AmongUsClient::Instance->AmHost)
		{
			return nullptr;
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"[SHR] つうか");
		CrewOrImpostorSet();
		OneOrNotListSet();
		AllRoleSetClass::AllRoleSet();
		SetCustomRoles();
		SyncSetting::CustomSyncSettings();
		ChacheManager::ResetChache();
		main::SendAllRoleChat();
		return sender;
	}

	void RoleSelectHandler::SpawnBots()
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			int impostor = PlayerControl::GameOptions::NumImpostors;
			int crewmate = 0;
			//ジャッカルがいるなら
			if (CustomOptions::JackalOption->getSelection() != 0)
			{
				for (int i = 0; i < (PlayerControl::GameOptions::NumImpostors + 2); i++)
				{
					PlayerControl *bot = BotManager::Spawn(L"[SHR] 暗転対策BOT" + std::to_wstring(i + 1));
					if (i == 0)
					{
						impostor++;
						bot->RpcSetRole(RoleTypes::Impostor);
					}
					if (i > 0)
					{
						crewmate++;
						bot->RpcSetRole(RoleTypes::Crewmate);
					}
				}
			}
			else if (CustomOptions::EgoistOption->getSelection() != 0 || CustomOptions::SheriffOption->getSelection() != 0 || CustomOptions::trueloverOption->getSelection() != 0 || CustomOptions::FalseChargesOption->getSelection() != 0 || CustomOptions::RemoteSheriffOption->getSelection() != 0 || CustomOptions::MadMakerOption->getSelection() != 0 || CustomOptions::SamuraiOption->getSelection() != 0 || CustomOptions::DemonOption->getSelection() != 0)
			{
				PlayerControl *bot1 = BotManager::Spawn(L"暗転対策BOT1");
				bot1->RpcSetRole(RoleTypes::Impostor);

				PlayerControl *bot2 = BotManager::Spawn(L"暗転対策BOT2");
				bot2->RpcSetRole(RoleTypes::Crewmate);

				PlayerControl *bot3 = BotManager::Spawn(L"暗転対策BOT3");
				bot3->RpcSetRole(RoleTypes::Crewmate);
				impostor++;
				crewmate++;
				crewmate++;
			}
			else if (CustomOptions::AssassinAndMarineOption->getSelection() != 0)
			{
				PlayerControl *bot1 = BotManager::Spawn(L"暗転対策BOT1");
				bot1->RpcSetRole(RoleTypes::Crewmate);
				crewmate++;
			}
			if (CustomOptions::SpyOption->getSelection() != 0)
			{
				for (int i = 0; i < CustomOptions::SpyPlayerCount->getFloat() - (crewmate - (impostor - PlayerControl::GameOptions::NumImpostors)) + 1; i++)
				{
					PlayerControl *bot1 = BotManager::Spawn(L"暗転対策BOT");
					bot1->RpcSetRole(RoleTypes::Crewmate);
					crewmate++;
				}
			}
			if (CustomOptions::BakeryOption->getSelection() != 0)
			{
				BotManager::Spawn(L"パン屋BOT")->Exiled();
			}
			else if (CustomOptions::AssassinAndMarineOption->getSelection() != 0)
			{
				BotManager::Spawn(ModTranslation::getString(L"AssassinAndMarineName") + L"BOT")->Exiled();
			}
		}
	}

	void RoleSelectHandler::SetCustomRoles()
	{
		std::vector<PlayerControl*> DesyncImpostors;
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::Jackal::JackalPlayer.begin(), RoleClass::Jackal::JackalPlayer.end());
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::Sheriff::SheriffPlayer.begin(), RoleClass::Sheriff::SheriffPlayer.end());
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::Demon::DemonPlayer.begin(), RoleClass::Demon::DemonPlayer.end());
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::truelover::trueloverPlayer.begin(), RoleClass::truelover::trueloverPlayer.end());
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::FalseCharges::FalseChargesPlayer.begin(), RoleClass::FalseCharges::FalseChargesPlayer.end());
		DesyncImpostors.insert(DesyncImpostors.end(), RoleClass::MadMaker::MadMakerPlayer.begin(), RoleClass::MadMaker::MadMakerPlayer.end());
		//インポスターにDesync
		std::vector<PlayerControl*> SetRoleEngineers;
		if (RoleClass::Jester::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::Jester::JesterPlayer.begin(), RoleClass::Jester::JesterPlayer.end());
		}
		if (RoleClass::JackalFriends::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::JackalFriends::JackalFriendsPlayer.begin(), RoleClass::JackalFriends::JackalFriendsPlayer.end());
		}
		if (RoleClass::MadMate::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::MadMate::MadMatePlayer.begin(), RoleClass::MadMate::MadMatePlayer.end());
		}
		if (RoleClass::MadStuntMan::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::MadStuntMan::MadStuntManPlayer.begin(), RoleClass::MadStuntMan::MadStuntManPlayer.end());
		}
		if (RoleClass::MadJester::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::MadJester::MadJesterPlayer.begin(), RoleClass::MadJester::MadJesterPlayer.end());
		}
		if (RoleClass::Fox::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::Fox::FoxPlayer.begin(), RoleClass::Fox::FoxPlayer.end());
		}
		if (RoleClass::MayorFriends::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::MayorFriends::MayorFriendsPlayer.begin(), RoleClass::MayorFriends::MayorFriendsPlayer.end());
		}
		if (RoleClass::Tuna::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::Tuna::TunaPlayer.begin(), RoleClass::Tuna::TunaPlayer.end());
		}
		SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::Technician::TechnicianPlayer.begin(), RoleClass::Technician::TechnicianPlayer.end());
		if (RoleClass::BlackCat::IsUseVent)
		{
			SetRoleEngineers.insert(SetRoleEngineers.end(), RoleClass::BlackCat::BlackCatPlayer.begin(), RoleClass::BlackCat::BlackCatPlayer.end());
		}
		//エンジニアに役職設定
		std::vector<PlayerControl*> DesyncShapeshifters;
		DesyncShapeshifters.insert(DesyncShapeshifters.end(), RoleClass::Arsonist::ArsonistPlayer.begin(), RoleClass::Arsonist::ArsonistPlayer.end());
		DesyncShapeshifters.insert(DesyncShapeshifters.end(), RoleClass::RemoteSheriff::RemoteSheriffPlayer.begin(), RoleClass::RemoteSheriff::RemoteSheriffPlayer.end());
		//Desync
		for (auto Player : DesyncImpostors)
		{
			if (!SuperNewRoles::PlayerControlHepler::IsMod(Player))
			{
				int PlayerCID = SuperNewRoles::ModHelpers::getClientId(Player);
				SuperNewRoles::CustomRpcSenderExtensions::RpcSetRole(sender, Player, RoleTypes::Impostor, PlayerCID);
				for (auto pc : PlayerControl::AllPlayerControls)
				{
					if (pc->PlayerId == Player->PlayerId)
					{
						continue;
					}
					SuperNewRoles::CustomRpcSenderExtensions::RpcSetRole(sender, pc, RoleTypes::Scientist, PlayerCID);
				}
				//他視点で科学者にするループ
				for (auto pc : PlayerControl::AllPlayerControls)
				{
					if (pc->PlayerId == Player->PlayerId)
					{
						continue;
					}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
