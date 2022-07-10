//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "CustomRPC.h"
#include "../ModHelpers.h"
#include "../Helpers/CachedPlayer.h"
#include "../Helpers/FastDestroyableSingleton.h"
#include "../Roles/RoleClass.h"
#include "../Roles/Sheriff.h"
#include "../Helpers/MapUtilities.h"
#include "../Roles/Arsonist.h"
#include "../Roles/Demon.h"
#include "../Main.h"
#include "../BotManager.h"
#include "../EndGame/EndGame.h"
#include "../Roles/RoleHelper.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../ChacheManager/main.h"
#include "../PlayerControlHepler.h"
#include "../Mode/SuperHostRoles/BlockTool.h"
#include "../Config.h"
#include "../Patch/ShareGameVersion.h"
#include "../Sabotage/Patch.h"
#include "../Mode/Detective/main.h"
#include "../CustomOption/CustomOptionModel.h"
#include "../Roles/Clergyman.h"
#include "../Mode/ModeHandler.h"
#include "../Mode/BattleRoyal/main.h"
#include "../SubmergedCompatibility.h"
#include "../CustomMsg.h"
#include "../TranslateDate.h"
#include "../EndGame/CustomEndReason.h"
#include "../Buttons/Buttons.h"
#include "../Sabotage/SabotageManager.h"
#include "../MapCustoms/4_Airship/SecretRoom.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomCosmetics::ShareCosmetics;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace SuperNewRoles::Sabotage;
using namespace UnityEngine;

namespace SuperNewRoles::CustomRPC
{

	void RPCProcedure::KunaiKill(unsigned char sourceid, unsigned char targetid)
	{
		PlayerControl *source = ModHelpers::playerById(sourceid);
		PlayerControl *target = ModHelpers::playerById(targetid);
		if (source == nullptr || target == nullptr)
		{
			return;
		}
		RPCMurderPlayer(sourceid, targetid, 0);
		SuperNewRoles::EndGame::FinalStatusPatch::FinalStatusData::FinalStatuses[target->PlayerId] = FinalStatus::Kill;

		if (targetid == CachedPlayer::LocalPlayer->PlayerId)
		{
			FastDestroyableSingleton<HudManager*>::getInstance().KillOverlay::ShowKillAnimation(target->Data, source->Data);
		}
	}

	void RPCProcedure::ChiefSidekick(unsigned char targetid)
	{
		RoleClass::Chief::SheriffPlayer.push_back(targetid);
		SetRole(targetid, static_cast<unsigned char>(RoleId::Sheriff));
		if (targetid == CachedPlayer::LocalPlayer->PlayerId)
		{
			Sheriff::ResetKillCoolDown();
			RoleClass::Sheriff::KillMaxCount = RoleClass::Chief::KillLimit;
		}
		UncheckedSetVanilaRole(targetid, 0);
	}

	void RPCProcedure::FixLights()
	{
		SwitchSystem *switchSystem = MapUtilities::getSystems()[SystemTypes::Electrical].TryCast<SwitchSystem*>();
		switchSystem->ActualSwitches = switchSystem->ExpectedSwitches;
	}

	void RPCProcedure::ArsonistDouse(unsigned char source, unsigned char target)
	{
		PlayerControl *TargetPlayer = ModHelpers::playerById(target);
		PlayerControl *SourcePlayer = ModHelpers::playerById(source);
		if (TargetPlayer == nullptr || SourcePlayer == nullptr)
		{
			return;
		}
		if (RoleClass::Arsonist::DouseDatas.find(source) == RoleClass::Arsonist::DouseDatas.end())
		{
			RoleClass::Arsonist::DouseDatas[source] = std::vector<PlayerControl*>();
		}
		if (!Arsonist::IsDoused(SourcePlayer, TargetPlayer))
		{
			RoleClass::Arsonist::DouseDatas[source].push_back(TargetPlayer);
		}
	}

	void RPCProcedure::DemonCurse(unsigned char source, unsigned char target)
	{
		PlayerControl *TargetPlayer = ModHelpers::playerById(target);
		PlayerControl *SourcePlayer = ModHelpers::playerById(source);
		if (TargetPlayer == nullptr || SourcePlayer == nullptr)
		{
			return;
		}
		if (RoleClass::Demon::CurseDatas.find(source) == RoleClass::Demon::CurseDatas.end())
		{
			RoleClass::Demon::CurseDatas[source] = std::vector<PlayerControl*>();
		}
		if (!Demon::IsCursed(SourcePlayer, TargetPlayer))
		{
			RoleClass::Demon::CurseDatas[source].push_back(TargetPlayer);
		}
	}

	void RPCProcedure::SetBot(unsigned char playerid)
	{
		SuperNewRolesPlugin::Logger->LogInfo(L"セットボット！！！！！！！！！");
		PlayerControl *player = ModHelpers::playerById(playerid);
		if (player == nullptr)
		{
			SuperNewRolesPlugin::Logger->LogInfo(L"nullなのでreturn");
			return;
		}
		SuperNewRolesPlugin::Logger->LogInfo(L"通過:" + player->name);
		if (BotManager::AllBots.empty())
		{
			BotManager::AllBots = std::vector<PlayerControl*>();
		}
		BotManager::AllBots.push_back(player);

	}

	void RPCProcedure::UncheckedProtect(unsigned char sourceid, unsigned char playerid, unsigned char colorid)
	{
		PlayerControl *player = ModHelpers::playerById(playerid);
		PlayerControl *source = ModHelpers::playerById(sourceid);
		if (player == nullptr || source == nullptr)
		{
			return;
		}
		source->ProtectPlayer(player, colorid);
	}

	void RPCProcedure::CustomEndGame(GameOverReason *reason, bool showAd)
	{
		CheckGameEndPatch::CustomEndGame(reason, showAd);
	}

	void RPCProcedure::UseStuntmanCount(unsigned char playerid)
	{
		auto player = ModHelpers::playerById(playerid);
		if (player == nullptr)
		{
			return;
		}
		if (SuperNewRoles::RoleHelpers::isRole(player, RoleId::MadStuntMan))
		{
			if (RoleClass::MadStuntMan::GuardCount.find(playerid) == RoleClass::MadStuntMan::GuardCount.end())
			{
				RoleClass::MadStuntMan::GuardCount[playerid] = (static_cast<int>(CustomOptions::MadStuntManMaxGuardCount->getFloat())) - 1;
			}
			else
			{
				RoleClass::MadStuntMan::GuardCount[playerid]--;
			}
		}
		else if (SuperNewRoles::RoleHelpers::isRole(player, RoleId::StuntMan))
		{
			if (RoleClass::StuntMan::GuardCount.find(playerid) == RoleClass::StuntMan::GuardCount.end())
			{
				RoleClass::StuntMan::GuardCount[playerid] = (static_cast<int>(CustomOptions::StuntManMaxGuardCount->getFloat())) - 1;
			}
			else
			{
				RoleClass::StuntMan::GuardCount[playerid]--;
			}
		}
	}

	void RPCProcedure::SetMadKiller(unsigned char sourceid, unsigned char targetid)
	{
		auto source = ModHelpers::playerById(sourceid);
		auto target = ModHelpers::playerById(targetid);
		if (source == nullptr || target == nullptr)
		{
			return;
		}
		SuperNewRoles::RoleHelpers::ClearRole(target);
		RoleClass::SideKiller::MadKillerPlayer.push_back(target);
		RoleClass::SideKiller::MadKillerPair.emplace(source->PlayerId, target->PlayerId);
		DestroyableSingleton<RoleManager*>::Instance->SetRole(target, RoleTypes::Crewmate);
		ChacheManager::ResetMyRoleChache();
		PlayerControlHepler::refreshRoleDescription(PlayerControl::LocalPlayer);
	}

	void RPCProcedure::UncheckedSetVanilaRole(unsigned char playerid, unsigned char roletype)
	{
		auto player = ModHelpers::playerById(playerid);
		if (player == nullptr)
		{
			return;
		}
		DestroyableSingleton<RoleManager*>::Instance->SetRole(player, static_cast<RoleTypes*>(roletype));
		player->Data->Role->Role = static_cast<RoleTypes*>(roletype);
	}


//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
