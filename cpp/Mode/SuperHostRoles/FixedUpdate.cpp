//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "FixedUpdate.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../ModHelpers.h"
#include "../../Main.h"
#include "../../Roles/RoleHelper.h"
#include "../ModeHandler.h"
#include "../../BotManager.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../../PlayerControlHepler.h"
#include "../../Roles/RoleClass.h"
#include "../../Roles/BlackCat.h"
#include "../../Roles/Madmate.h"
#include "../../Roles/MadMayor.h"
#include "../../Roles/JackalFriends.h"
#include "Roles/Jackal.h"
#include "../../Roles/Jackal.h"
#include "../../Roles/Demon.h"
#include "../../Roles/Arsonist.h"
#include "../../Roles/Mafia.h"
#include "../../Intro/IntroDate.h"
#include "../../Patch/TaskCount.h"
#include "../../Helpers/RPCHelper.h"
#include "../../Helpers/FastDestroyableSingleton.h"
#include "../../Patch/PlayerControlPatch.h"
#include "../../Patch/SetNames.h"
#include "BlockTool.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles::Roles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Patches;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

std::unordered_map<int, std::wstring> FixedUpdate::DefaultName;
int FixedUpdate::UpdateDate = 0;

	void FixedUpdate::CoShowIntroPatch::Prefix(HudManager *__instance)
	{
		DefaultName = std::unordered_map<int, std::wstring>();
		for (auto pc : CachedPlayer::AllPlayers)
		{
			//SuperNewRolesPlugin.Logger.LogInfo($"{pc.PlayerId}:{pc.name}:{pc.nameText().text}");
			DefaultName[pc->PlayerId] = pc->PlayerControl->name;
			SuperNewRoles::ModHelpers::nameText(pc->PlayerControl)->text = pc->PlayerControl->name;
		}
	}

	std::wstring FixedUpdate::getDefaultName(PlayerControl *player)
	{
		auto playerid = player->PlayerId;
		if (DefaultName.find(playerid) != DefaultName.end())
		{
			return DefaultName[playerid];
		}
		else
		{
			DefaultName[playerid] = player->Data->PlayerName;
			return DefaultName[playerid];
		}
	}

	void FixedUpdate::RoleFixedUpdate()
	{
	} /*

	void FixedUpdate::SetRoleName(PlayerControl *player, bool IsUnchecked)
	{
		auto caller = new System::Diagnostics::StackFrame(1, false);
		auto callerMethod = caller->GetMethod();
		std::wstring callerMethodName = callerMethod->Name;
		std::wstring callerClassName = callerMethod->DeclaringType.FullName;
		SuperNewRolesPlugin::Logger->LogInfo(L"[SHR:FixedUpdate]" + player->name + L"への(IsCommsなしの)SetRoleNameが" + callerClassName + L"." + callerMethodName + L"から呼び出されました。");
		SetRoleName(player, RoleHelpers::IsComms(), IsUnchecked);

		delete caller;
	}

	void FixedUpdate::SetRoleName(PlayerControl *player, bool commsActive, bool IsUnchecked)
	{
		if (!ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return;
		}
		if (SuperNewRoles::BotManager::IsBot(player) || !AmongUsClient::Instance->AmHost)
		{
			return;
		}

		auto caller = new System::Diagnostics::StackFrame(1, false);
		auto callerMethod = caller->GetMethod();
		std::wstring callerMethodName = callerMethod->Name;
		std::wstring callerClassName = callerMethod->DeclaringType.FullName;
		SuperNewRolesPlugin::Logger->LogInfo(L"[SHR: FixedUpdate]" + player->name + L"へのSetRoleNameが" + callerClassName + L"." + callerMethodName + L"から呼び出されました。");

		//if (UpdateTime.ContainsKey(player.PlayerId) && UpdateTime[player.PlayerId] > 0) return;

		//UpdateTime[player.PlayerId] = UpdateDefaultTime;

		std::vector<PlayerControl*> DiePlayers;
		for (auto p : CachedPlayer::AllPlayers)
		{
			if (p->PlayerId != 0 && p->PlayerId != player->PlayerId && SuperNewRoles::BotManager::IsPlayer(p))
			{
				if (SuperNewRoles::RoleHelpers::isDead(p) || SuperNewRoles::RoleHelpers::isRole(p, RoleId::God))
				{
					DiePlayers.push_back(p);
				}
			}
		}
		//必要がないなら処理しない
		if (SuperNewRoles::PlayerControlHepler::IsMod(player) && DiePlayers.size() < 1)
		{
			delete caller;
			return;
		}

		std::wstring Name = SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(player);
		std::wstring NewName = L"";
		std::wstring MySuffix = L"";
		std::unordered_map<unsigned char, std::wstring> ChangePlayers;

		for (auto CelebrityPlayer : RoleClass::Celebrity::CelebrityPlayer)
		{
			if (CelebrityPlayer == player)
			{
				continue;
			}
			ChangePlayers.emplace(CelebrityPlayer->PlayerId, ModHelpers::cs(RoleClass::Celebrity::color, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(CelebrityPlayer)));
		}

		if (Madmate::CheckImpostor(player) || MadMayor::CheckImpostor(player) || SuperNewRoles::RoleHelpers::isRole(player, RoleId::Marine) || BlackCat::CheckImpostor(player))
		{
			for (auto Impostor : CachedPlayer::AllPlayers)
			{
				if (SuperNewRoles::RoleHelpers::isImpostor(Impostor) && SuperNewRoles::BotManager::IsPlayer(Impostor))
				{
					if (ChangePlayers.find(Impostor->PlayerId) == ChangePlayers.end())
					{
						ChangePlayers.emplace(Impostor->PlayerId, ModHelpers::cs(RoleClass::ImpostorRed, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(Impostor)));
					}
				}
			}
		}
		else if (JackalFriends::CheckJackal(player))
		{
			for (auto Jackal : RoleClass::Jackal::JackalPlayer)
			{
				if (!Jackal->Data->Disconnected)
				{
					if (ChangePlayers.find(Jackal->PlayerId) == ChangePlayers.end())
					{
						ChangePlayers.emplace(Jackal->PlayerId, ModHelpers::cs(RoleClass::Jackal::color, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(Jackal)));
					}
					else
					{
						ChangePlayers[Jackal->PlayerId] = ModHelpers::cs(RoleClass::Jackal::color, ChangePlayers[Jackal->PlayerId]);
					}
				}
			}
		}
		else if (SuperNewRoles::RoleHelpers::isRole(player, RoleId::Demon))
		{
			if (RoleClass::Demon::IsCheckImpostor)
			{
				for (auto Impostor : CachedPlayer::AllPlayers)
				{
					if (SuperNewRoles::RoleHelpers::isImpostor(Impostor) && SuperNewRoles::BotManager::IsPlayer(Impostor))
					{
						if (ChangePlayers.find(Impostor->PlayerId) == ChangePlayers.end())
						{
							ChangePlayers.emplace(Impostor->PlayerId, ModHelpers::cs(RoleClass::ImpostorRed, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(Impostor)));
						}
						else
						{
							ChangePlayers[Impostor->PlayerId] = ModHelpers::cs(RoleClass::ImpostorRed, ChangePlayers[Impostor->PlayerId]);
						}
					}
				}
			}
			for (auto CursePlayer : Demon::GetIconPlayers(player))
			{
				if (SuperNewRoles::BotManager::IsPlayer(CursePlayer))
				{
					if (ChangePlayers.find(CursePlayer->PlayerId) == ChangePlayers.end())
					{
						ChangePlayers.emplace(CursePlayer->PlayerId, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(CursePlayer) + ModHelpers::cs(RoleClass::Demon::color, L" ▲"));
					}
					else
					{
						ChangePlayers[CursePlayer->PlayerId] = ChangePlayers[CursePlayer->PlayerId] + ModHelpers::cs(RoleClass::Demon::color, L" ▲");
					}
				}
			}
		}
		else if (SuperNewRoles::RoleHelpers::isRole(player, RoleId::Arsonist))
		{
			for (auto DousePlayer : Arsonist::GetIconPlayers(player))
			{
				if (SuperNewRoles::BotManager::IsPlayer(DousePlayer))
				{
					if (ChangePlayers.find(DousePlayer->PlayerId) == ChangePlayers.end())
					{
						ChangePlayers.emplace(DousePlayer->PlayerId, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(DousePlayer) + ModHelpers::cs(RoleClass::Arsonist::color, L" §"));
					}
					else
					{
						ChangePlayers[DousePlayer->PlayerId] = ChangePlayers[DousePlayer->PlayerId] + ModHelpers::cs(RoleClass::Arsonist::color, L" §");
					}
				}
			}
		}

		if (SuperNewRoles::RoleHelpers::IsLovers(player))
		{
			auto suffix = ModHelpers::cs(RoleClass::Lovers::color, L" ♥");
			PlayerControl *Side = SuperNewRoles::RoleHelpers::GetOneSideLovers(player);
			std::wstring name = SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(Side);
			if (ChangePlayers.find(Side->PlayerId) == ChangePlayers.end())
			{
				ChangePlayers.emplace(Side->PlayerId, SuperNewRoles::Mode::SuperHostRoles::FixedUpdate::getDefaultName(Side) + suffix);
			}
			else
			{
				ChangePlayers[Side->PlayerId] = ChangePlayers[Side->PlayerId] + suffix;
			}
			MySuffix += suffix;
		}

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
