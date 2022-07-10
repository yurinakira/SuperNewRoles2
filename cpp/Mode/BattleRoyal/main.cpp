//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "main.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Buttons/Buttons.h"
#include "../../Helpers/FastDestroyableSingleton.h"
#include "../../Roles/RoleHelper.h"
#include "../../Helpers/RPCHelper.h"
#include "../../TranslateDate.h"
#include "../../ModHelpers.h"
#include "../../Roles/RoleClass.h"
#include "../ModeHandler.h"
#include "../../LateTask.h"
#include "../SuperHostRoles/CoEnterVent.h"
#include "../PlusModeHandler.h"
#include "../../CustomRPC/CustomRPC.h"
#include "../SuperHostRoles/MorePatch.h"
#include "../../Main.h"
#include "../SuperHostRoles/SyncSetting.h"
#include "BROption.h"
#include "../SuperHostRoles/Helpers.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::BattleRoyal
{

	void main::FixedUpdate()
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (IsStart)
		{
			CachedPlayer::LocalPlayer->Data->Role->CanUseKillButton = true;
			if (!IsTeamBattle)
			{
				FastDestroyableSingleton<HudManager*>::getInstance().KillButton::SetTarget(Buttons::HudManagerStartPatch::setTarget());
			}
			int alives = 0;
			int allplayer = 0;
			for (auto p : CachedPlayer::AllPlayers)
			{
				allplayer++;
				if (SuperNewRoles::RoleHelpers::isAlive(p))
				{
					alives++;
				}
			}
			if (AlivePlayer != alives || AllPlayer != allplayer)
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (!p->Data->Disconnected)
					{
						SuperNewRoles::Helpers::RPCHelper::RpcSetNamePrivate(p, L"(" + std::to_wstring(alives) + L"/" + std::to_wstring(allplayer) + L")");
					}
				}
				AlivePlayer = alives;
				AllPlayer = allplayer;
			}
		}
		else
		{
			if (IsCountOK)
			{
				StartSeconds -= Time::fixedDeltaTime;
			}
			UpdateTime -= Time::fixedDeltaTime;
			if (UpdateTime <= 0)
			{
				for (auto p : CachedPlayer::AllPlayers)
				{
					if (!p->Data->Disconnected)
					{
						SuperNewRoles::Helpers::RPCHelper::RpcSetNamePrivate(p, ModTranslation::getString(L"BattleRoyalRemaining") + std::to_wstring(static_cast<int>(StartSeconds) + 1) + ModTranslation::getString(L"second"));
					}
				}
				UpdateTime += 1.0f;
			}
			if (StartSeconds <= 0)
			{
				IsStart = true;
				for (auto team : Teams)
				{
					if (SuperNewRoles::ModHelpers::IsCheckListPlayerControl(team, PlayerControl::LocalPlayer))
					{
						for (auto p : team)
						{
							if (p->PlayerId != 0)
							{
								PlayerControl::LocalPlayer::RpcSetNamePrivate(ModHelpers::cs(RoleClass::ImpostorRed, ModTranslation::getString(L"Player")), p);
							}
						}
					}
				}
			}
		}
	}

int main::AlivePlayer = 0;
int main::AllPlayer = 0;
bool main::IsStart = false;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerPhysics __instance, [HarmonyArgument(0)] int id)
	bool main::CoExitVentPatch::Prefix(PlayerPhysics *__instance, int id)
	{
		VentData[__instance->myPlayer.PlayerId] = std::nullopt;
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerPhysics __instance, [HarmonyArgument(0)] int id)
	bool main::CoEnterVentPatch::Prefix(PlayerPhysics *__instance, int id)
	{
		if (AmongUsClient::Instance->AmHost)
		{
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers}))
			{
				MessageWriter *writer = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, static_cast<unsigned char>(RpcCalls::BootFromVent), SendOption::Reliable, -1);
				writer->WritePacked(127);
				AmongUsClient::Instance->FinishRpcImmediately(writer);
				new LateTask([&] ()
				{
					int clientId = __instance->myPlayer.getClientId();
					MessageWriter *writer2 = AmongUsClient::Instance->StartRpcImmediately(__instance->NetId, static_cast<unsigned char>(RpcCalls::BootFromVent), SendOption::Reliable, clientId);
					writer2->Write(id);
					AmongUsClient::Instance->FinishRpcImmediately(writer2);
					__instance->myPlayer->inVent = false;
				}, 0.5f, L"Anti Vent");
				return false;
			}
			else if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
			{
				bool data = CoEnterVent::Prefix(__instance, id);
				if (data)
				{
					VentData[__instance->myPlayer.PlayerId] = id;
				}
				return data;
			}
		}
		VentData[__instance->myPlayer.PlayerId] = id;
		return true;
	}

std::unordered_map<unsigned char, std::optional<int>> main::VentData;

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
	bool main::RepairSystemPatch::Prefix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount)
	{
		if (PlusModeHandler::isMode(PlusModeId::NotSabotage))
		{
			return false;
		}
		if ((ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}) || ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers})) && (systemType == SystemTypes::Sabotage || systemType == SystemTypes::Doors))
		{
			return false;
		}
		if (systemType == SystemTypes::Electrical && 0 <= amount && amount <= 4 && SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::MadMate))
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			bool returndata = MorePatch::RepairSystem(__instance, systemType, player, amount);
			return returndata;
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
	void main::RepairSystemPatch::Postfix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount)
	{
		if (!RoleHelpers::IsSabotage())
		{
			new LateTask([&] ()
			{
			for (auto p : RoleClass::Technician::TechnicianPlayer)
			{
					if (p->inVent && SuperNewRoles::RoleHelpers::isAlive(p) && VentData.find(p->PlayerId) != VentData.end() && VentData[p->PlayerId])
					{
						p->MyPhysics.RpcBootFromVent(static_cast<int>(VentData[p->PlayerId]));
					}
			}
			}, 0.1f, L"TecExitVent");
		}
		SuperNewRolesPlugin::Logger->LogInfo(player->Data->PlayerName + L" => " + systemType + L" : " + std::to_wstring(amount));
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			SyncSetting::CustomSyncSettings();
			if (systemType == SystemTypes::Comms)
			{
				Mode::SuperHostRoles::FixedUpdate::SetRoleNames();
			}
		}
	}

std::vector<PlayerControl*> main::Winners;
bool main::IsViewAlivePlayer = false;

	bool main::EndGameCheck(ShipStatus *__instance, SuperNewRoles::EndGame::CheckGameEndPatch::PlayerStatistics *statistics)
	{
		if (IsTeamBattle)
		{
			if (!IsSeted)
			{
				return false;
			}
			std::vector<PlayerControl*> players;

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
