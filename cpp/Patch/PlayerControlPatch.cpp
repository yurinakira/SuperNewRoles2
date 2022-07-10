//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "PlayerControlPatch.h"
#include "../Mode/SuperHostRoles/SyncSetting.h"
#include "../Roles/RoleClass.h"
#include "../BotManager.h"
#include "../Mode/ModeHandler.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleHelper.h"
#include "../LateTask.h"
#include "../Roles/Sheriff.h"
#include "../EndGame/FinalStatus.h"
#include "../CustomOption/CustomOptionDate.h"
#include "../Mode/SuperHostRoles/FixedUpdate.h"
#include "../Helpers/CachedPlayer.h"
#include "../Roles/SelfBomber.h"
#include "../Roles/Samurai.h"
#include "../Roles/Arsonist.h"
#include "../Helpers/RPCHelper.h"
#include "../EndGame/CustomEndReason.h"
#include "../EndGame/EndGame.h"
#include "../Roles/Kunoichi.h"
#include "../Main.h"
#include "../Mode/BattleRoyal/main.h"
#include "../Mode/SuperHostRoles/Helpers.h"
#include "../Roles/Demon.h"
#include "../Roles/Mafia.h"
#include "../Mode/Detective/main.h"
#include "../Roles/EvilEraser.h"
#include "../Roles/EvilGambler.h"
#include "../OutfitManager.h"
#include "../Roles/Fox.h"
#include "DeadPlayer.h"
#include "../Roles/SerialKiller.h"
#include "../Roles/Seer.h"
#include "../Mode/SuperHostRoles/MurderPlayer.h"
#include "../Roles/Levelinger.h"
#include "../Roles/Minimalist.h"
#include "../Helpers/MapUtilities.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::CustomOption;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::EndGame;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Intro;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;
using namespace SuperNewRoles::Patch;
using namespace SuperNewRoles::Roles;
using namespace UnityEngine;

namespace SuperNewRoles::Patches
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target, [HarmonyArgument(1)] bool shouldAnimate)
	bool RpcShapesihftPatch::Prefix(PlayerControl *__instance, PlayerControl *target, bool shouldAnimate)
	{
		SyncSetting::CustomSyncSettings();
		if (RoleClass::Assassin::TriggerPlayer != nullptr)
		{
			return false;
		}
		if (SuperNewRoles::BotManager::IsBot(target))
		{
			return true;
		}
		if (__instance->PlayerId == target->PlayerId)
		{
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}) && AmongUsClient::Instance->AmHost)
			{
				if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::RemoteSheriff))
				{
					__instance->RpcProtectPlayer(__instance, 0);
					new LateTask([&] ()
					{
						__instance->RpcMurderPlayer(__instance);
					}, 0.5f);
				}
			}
			return true;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			switch (SuperNewRoles::RoleHelpers::getRole(__instance))
			{
				case RoleId::RemoteSheriff:
					if (AmongUsClient::Instance->AmHost)
					{
						if (SuperNewRoles::RoleHelpers::isDead(target))
						{
							return true;
						}
						if (RoleClass::RemoteSheriff::KillCount.find(__instance->PlayerId) == RoleClass::RemoteSheriff::KillCount.end() || RoleClass::RemoteSheriff::KillCount[__instance->PlayerId] >= 1)
						{
							if (!Sheriff::IsRemoteSheriffKill(target) || SuperNewRoles::RoleHelpers::isRole(target, RoleId::RemoteSheriff))
							{
								FinalStatusPatch::FinalStatusData::FinalStatuses[__instance->PlayerId] = FinalStatus::SheriffMisFire;
								__instance->RpcMurderPlayer(__instance);
								return true;
							}
							else
							{
								FinalStatusPatch::FinalStatusData::FinalStatuses[target->PlayerId] = FinalStatus::SheriffKill;
								if (RoleClass::RemoteSheriff::KillCount.find(__instance->PlayerId) != RoleClass::RemoteSheriff::KillCount.end())
								{
									RoleClass::RemoteSheriff::KillCount[__instance->PlayerId]--;
								}
								else
								{
									RoleClass::RemoteSheriff::KillCount[__instance->PlayerId] = static_cast<int>(CustomOptions::RemoteSheriffKillMaxCount->getFloat()) - 1;
								}
								if (RoleClass::RemoteSheriff::IsKillTeleport)
								{
									SuperNewRoles::Patches::CheckMurderPatch::RpcMurderPlayerCheck(__instance, target);
								}
								else
								{
									target->RpcMurderPlayer(target);
									__instance->RpcProtectPlayer(__instance, 0);
								}
								Mode::SuperHostRoles::FixedUpdate::SetRoleName(__instance);
								return true;
							}
						}
						else
						{
							return true;
						}
					}
					return true;
				case RoleId::SelfBomber:
					if (AmongUsClient::Instance->AmHost)
					{
						for (auto p : CachedPlayer::AllPlayers)
						{
							if (SuperNewRoles::RoleHelpers::isAlive(p) && p->PlayerId != __instance->PlayerId)
							{
								if (SelfBomber::GetIsBomb(__instance, p))
								{
									SuperNewRoles::Patches::CheckMurderPatch::RpcMurderPlayerCheck(__instance, p);
								}
							}
						}
						__instance->RpcMurderPlayer(__instance);
					}
					return false;
				case RoleId::Samurai:
					if (!std::find(RoleClass::Samurai::SwordedPlayer.begin(), RoleClass::Samurai::SwordedPlayer.end(), __instance->PlayerId) != RoleClass::Samurai::SwordedPlayer.end())
					{
						if (AmongUsClient::Instance->AmHost || !RoleClass::Samurai::Sword)
						{
							for (auto p : CachedPlayer::AllPlayers)
							{
								if (SuperNewRoles::RoleHelpers::isAlive(p) && p->PlayerId != __instance->PlayerId)
								{
									if (Samurai::Getsword(__instance, p))
									{
										SuperNewRoles::Patches::CheckMurderPatch::RpcMurderPlayerCheck(__instance, p);
										Samurai::IsSword();
									}
								}
							}
						}
						RoleClass::Samurai::SwordedPlayer.push_back(__instance->PlayerId);
					}
					return false;
				case RoleId::Arsonist:
					if (AmongUsClient::Instance->AmHost)
					{
						for (auto p : RoleClass::Arsonist::ArsonistPlayer)
						{
							if (Arsonist::IsWin(p))
							{
								RPCProcedure::ShareWinner(CachedPlayer::LocalPlayer->PlayerId);
								MessageWriter *Writer = AmongUsClient::Instance->StartRpcImmediately(PlayerControl::LocalPlayer::NetId, static_cast<unsigned char>(CustomRPC::CustomRPC::ShareWinner), SendOption::Reliable, -1);
								Writer->Write(p->PlayerId);
								AmongUsClient::Instance->FinishRpcImmediately(Writer);

								Writer = RPCHelper::StartRPC(CustomRPC::CustomRPC::SetWinCond);
								Writer->Write(static_cast<unsigned char>(CustomGameOverReason::ArsonistWin));
								SuperNewRoles::Helpers::RPCHelper::EndRPC(Writer);
								RPCProcedure::SetWinCond(static_cast<unsigned char>(CustomGameOverReason::ArsonistWin));

								RoleClass::Arsonist::TriggerArsonistWin = true;
								EndGame::AdditionalTempData::winCondition = EndGame::WinCondition::ArsonistWin;
								// SuperNewRolesPlugin.Logger.LogInfo("CheckAndEndGame");
								__instance->enabled = false;
								ShipStatus::RpcEndGame(static_cast<GameOverReason*>(EndGame::CustomGameOverReason::ArsonistWin), false);
								return true;
							}
						}
					}
					return false;
				case RoleId::SuicideWisher:
					if (AmongUsClient::Instance->AmHost)
					{
						__instance->RpcMurderPlayer(__instance);
					}
					return false;
			}
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
	bool CheckProtectPatch::Prefix(PlayerControl *__instance, PlayerControl *target)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return false;
		}
		return true;
	}

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(ShapeshifterMinigame __instance, [HarmonyArgument(0)] PlayerControl player)

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
