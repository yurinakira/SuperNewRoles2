#include "Patch.h"
#include "../../Helpers/MapUtilities.h"
#include "../../Helpers/CachedPlayer.h"
#include "../../Roles/RoleHelper.h"
#include "../../ModHelpers.h"
#include "../../Roles/RoleClass.h"
#include "../../Helpers/FastDestroyableSingleton.h"

using namespace HarmonyLib;
using namespace Hazel;
using namespace UnityEngine;

namespace SuperNewRoles::Mode::HideAndSeek
{

	void Patch::RepairSystemPatch::Postfix(PlayerControl *__instance)
	{
		for (PlayerTask *task : PlayerControl::LocalPlayer::myTasks)
		{
			if (task->TaskType == TaskTypes::FixLights)
			{
				MapUtilities::CachedShipStatus->RepairSystem(SystemTypes::Electrical, PlayerControl::LocalPlayer, static_cast<unsigned char>(16));
				MapUtilities::CachedShipStatus->RepairSystem(SystemTypes::Laboratory, PlayerControl::LocalPlayer, static_cast<unsigned char>(16));
				MapUtilities::CachedShipStatus->RepairSystem(SystemTypes::Reactor, PlayerControl::LocalPlayer, static_cast<unsigned char>(16));
				MapUtilities::CachedShipStatus->RepairSystem(SystemTypes::LifeSupp, PlayerControl::LocalPlayer, static_cast<unsigned char>(16));
			}
			else if (task->TaskType == TaskTypes::RestoreOxy)
			{
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::LifeSupp, 0 | 64);
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::LifeSupp, 1 | 64);
			}
			else if (task->TaskType == TaskTypes::ResetReactor)
			{
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Reactor, 16);
			}
			else if (task->TaskType == TaskTypes::ResetSeismic)
			{
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Laboratory, 16);
			}
			else if (task->TaskType == TaskTypes::FixComms)
			{
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Comms, 16 | 0);
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Comms, 16 | 1);
			}
			else if (task->TaskType == TaskTypes::StopCharles)
			{
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Reactor, 0 | 16);
				MapUtilities::CachedShipStatus->RpcRepairSystem(SystemTypes::Reactor, 1 | 16);
			}
		}
		for (PlainDoor *door : MapUtilities::CachedShipStatus->AllDoors)
		{
			door->SetDoorway(true);
		}
	}

	void Patch::HASFixed::Postfix(PlayerControl *__instance)
	{
		if (AmongUsClient::Instance->AmHost)
		{
			for (auto player : CachedPlayer::AllPlayers)
			{
				if (SuperNewRoles::RoleHelpers::isImpostor(player))
				{
					player->RpcSetName(ModHelpers::cs(Roles->RoleClass::ImpostorRed, player->Data->GetPlayerName(PlayerOutfitType::Default)));
				}
				else
				{
					Color32 tempVar(0, 255, 0, std::numeric_limits<unsigned char>::max());
					player->RpcSetName(ModHelpers::cs(&tempVar, player->Data->GetPlayerName(PlayerOutfitType::Default)));
				}
			}
			RepairSystemPatch::Postfix(__instance);
		}
		FastDestroyableSingleton<HudManager*>::getInstance().ReportButton->Hide();
		FastDestroyableSingleton<HudManager*>::getInstance().AbilityButton->Hide();
	}
}
