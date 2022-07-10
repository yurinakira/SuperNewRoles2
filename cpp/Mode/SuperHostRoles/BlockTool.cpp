//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "BlockTool.h"
#include "../../MapOptions/MapOption.h"
#include "../ModeHandler.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../PlayerControlHepler.h"
#include "../../Roles/RoleHelper.h"
#include "../../ModHelpers.h"
#include "../../MapCustoms/MapCustom.h"
#include "../../Helpers/MapUtilities.h"
#include "../../Main.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace InnerNet;
using namespace SuperNewRoles::MapOptions;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::SuperHostRoles
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(ShipStatus __instance, [HarmonyArgument(0)] SystemTypes systemType, [HarmonyArgument(1)] PlayerControl player, [HarmonyArgument(2)] byte amount)
	void BlockTool::RepairSystemPatch::Prefix(ShipStatus *__instance, SystemTypes *systemType, PlayerControl *player, unsigned char amount)
	{
		if (systemType == SystemTypes::Security)
		{
			if (amount == 1)
			{
				if (!std::find(CameraPlayers.begin(), CameraPlayers.end(), player->PlayerId) != CameraPlayers.end())
				{
					CameraPlayers.push_back(player->PlayerId);
				}
			}
			else
			{
				if (std::find(CameraPlayers.begin(), CameraPlayers.end(), player->PlayerId) != CameraPlayers.end())
				{
					CameraPlayers.Remove(player->PlayerId);
				}
			}
		}
		else if (systemType == SystemTypes::Comms)
		{
			IsCom = !IsCom;
		}
	}

std::vector<unsigned char> BlockTool::CameraPlayers;
std::vector<unsigned char> BlockTool::OldDesyncCommsPlayers;
float BlockTool::UsableDistance = 1.5f;
int BlockTool::Count = 0;
bool BlockTool::IsCom = false;
float BlockTool::CameraTime = 0;
float BlockTool::AdminTime = 0;
float BlockTool::VitalTime = 0;

	void BlockTool::FixedUpdate()
	{
		Count--;
		if (Count > 0)
		{
			return;
		}
		Count = 3;
		if ((!MapOption::UseAdmin || !MapOption::UseVitalOrDoorLog || !MapOption::UseCamera) && !ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			for (auto p : CachedPlayer::AllPlayers)
			{
				try
				{
					if (SuperNewRoles::RoleHelpers::isAlive(p) && !SuperNewRoles::PlayerControlHepler::IsMod(p))
					{
						auto cid = SuperNewRoles::ModHelpers::getClientId(p);
						bool IsGuard = false;
						Vector2 *playerposition = p->GetTruePosition();
						//カメラチェック
						if (!MapOption::UseCamera)
						{
							if (std::find(CameraPlayers.begin(), CameraPlayers.end(), p->PlayerId) != CameraPlayers.end())
							{
								IsGuard = true;
							}
						}
						//アドミンチェック
						if (!MapOption::UseAdmin)
						{
							auto AdminDistance = Vector2::Distance(playerposition, GetAdminTransform());
							if (AdminDistance <= UsableDistance)
							{
								IsGuard = true;
							}
						}
						//Polus用のアドミンチェック。Polusはアドミンが2つあるから
						if (!IsGuard && PlayerControl::GameOptions->MapId == 2 && !MapOption::UseAdmin)
						{
							Vector2 tempVar(24.66107f, -21.523f);
							auto AdminDistance = Vector2::Distance(playerposition, &tempVar);
							if (AdminDistance <= UsableDistance)
							{
								IsGuard = true;
							}
						}
						//AirShip(アーカイブ)用のアドミンチェック。AirShipはアドミンが2つあるから
						if (!IsGuard && PlayerControl::GameOptions->MapId == 4 && !MapOption::UseAdmin || !IsGuard && PlayerControl::GameOptions->MapId == 4 && MapCustoms::MapCustom::RecordsAdminDestroy->getBool() && MapOption::MapOptionSetting->getBool())
						{
							Vector2 tempVar2(19.9f, 12.9f);
							auto AdminDistance = Vector2::Distance(playerposition, &tempVar2);
							if (AdminDistance <= UsableDistance)
							{
								IsGuard = true;
							}
						}
						//バイタルもしくはドアログを防ぐ
						if (!IsGuard && !MapOption::UseVitalOrDoorLog)
						{
							float distance = UsableDistance;
							if (PlayerControl::GameOptions->MapId == 2)
							{
								distance += 0.5f;
							}
							auto AdminDistance = Vector2::Distance(playerposition, GetVitalOrDoorLogTransform());
							if (AdminDistance <= distance)
							{
								IsGuard = true;
							}
						}
						if (IsGuard && !p->inVent)
						{
							if (!std::find(OldDesyncCommsPlayers.begin(), OldDesyncCommsPlayers.end(), p->PlayerId) != OldDesyncCommsPlayers.end())
							{
								OldDesyncCommsPlayers.push_back(p->PlayerId);
							}
							MessageWriter *SabotageWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, cid);
							SabotageWriter->Write(static_cast<unsigned char>(SystemTypes::Comms));
							MessageExtensions::WriteNetObject(SabotageWriter, p);
							SabotageWriter->Write(static_cast<unsigned char>(128));
							AmongUsClient::Instance->FinishRpcImmediately(SabotageWriter);
						}
						else
						{
							if (!IsCom && std::find(OldDesyncCommsPlayers.begin(), OldDesyncCommsPlayers.end(), p->PlayerId) != OldDesyncCommsPlayers.end())
							{
								OldDesyncCommsPlayers.Remove(p->PlayerId);
								MessageWriter *SabotageFixWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, cid);
								SabotageFixWriter->Write(static_cast<unsigned char>(SystemTypes::Comms));
								MessageExtensions::WriteNetObject(SabotageFixWriter, p);
								SabotageFixWriter->Write(static_cast<unsigned char>(16));
								AmongUsClient::Instance->FinishRpcImmediately(SabotageFixWriter);

								if (PlayerControl::GameOptions->MapId == 4)
								{
									SabotageFixWriter = AmongUsClient::Instance->StartRpcImmediately(MapUtilities::CachedShipStatus->NetId, static_cast<unsigned char>(RpcCalls::RepairSystem), SendOption::Reliable, cid);
									SabotageFixWriter->Write(static_cast<unsigned char>(SystemTypes::Comms));
									MessageExtensions::WriteNetObject(SabotageFixWriter, p);
									SabotageFixWriter->Write(static_cast<unsigned char>(17));
									AmongUsClient::Instance->FinishRpcImmediately(SabotageFixWriter);
								}
							}
						}
					}
				}
				catch (const std::runtime_error &e)
				{
					SuperNewRolesPlugin::Logger->LogError(e);
				}
			}
		}
	}

	Vector2 *BlockTool::GetAdminTransform()
	{
		if (PlayerControl::GameOptions->MapId == 0)
		{
			return new Vector2(3.48f, -8.624401f);
		}
		else if (PlayerControl::GameOptions->MapId == 1)
		{
			return new Vector2(21.024f, 19.095f);
		}
		else if (PlayerControl::GameOptions->MapId == 2)
		{
			return new Vector2(23.13707f, -21.523f);
		}
		else if (PlayerControl::GameOptions->MapId == 3)
		{
			return new Vector2(-3.48f, -8.624401f);
		}
		else if (PlayerControl::GameOptions->MapId == 4)
		{
			return new Vector2(-22.323f, 0.9099998f);
		}
		return new Vector2(1000, 1000);
	}

	Vector2 *BlockTool::GetCameraTransform()
	{
		if (PlayerControl::GameOptions->MapId == 0)
		{
			return new Vector2(-12.93658f, -2.790947f);
		}
		else if (PlayerControl::GameOptions->MapId == 2)
		{

//====================================================================================================
//End of the allowed output for the Free Edition of C# to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================
