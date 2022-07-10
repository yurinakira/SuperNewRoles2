#include "Lovers.h"
#include "RoleHelper.h"
#include "RoleClass.h"
#include "../ChacheManager/main.h"
#include "../Mode/ModeHandler.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Helpers/RPCHelper.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;

namespace SuperNewRoles::Roles
{

	void Lovers::HandleDisconnectPatch::Postfix(GameData *__instance, PlayerControl *player, DisconnectReasons *reason)
	{
		if (AmongUsClient::Instance->GameState == InnerNet::InnerNetClient::GameStates::Started)
		{
			if (SuperNewRoles::RoleHelpers::IsLovers(player))
			{
				RoleClass::Lovers::LoversPlayer.RemoveAll([&] (std::any x)
				{
					x::TrueForAll([&] (std::any x2)
					{
							return x2->PlayerId == player->PlayerId;
					});
				});
				ChacheManager::ResetLoversChache();
			}
			if (SuperNewRoles::RoleHelpers::IsQuarreled(player) && SuperNewRoles::RoleHelpers::isAlive(player))
			{
				RoleClass::Quarreled::QuarreledPlayer.RemoveAll([&] (std::any x)
				{
					x::TrueForAll([&] (std::any x2)
					{
							return x2->PlayerId == player->PlayerId;
					});
				});
				ChacheManager::ResetQuarreledChache();
			}
			if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
			{
				if (SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::SideKiller))
				{
					auto sideplayer = RoleClass::SideKiller::getSidePlayer(PlayerControl::LocalPlayer);
					if (sideplayer != nullptr)
					{
						if (!RoleClass::SideKiller::IsUpMadKiller)
						{
							SuperNewRoles::Helpers::RPCHelper::RPCSetRoleUnchecked(sideplayer, RoleTypes::Impostor);
							RoleClass::SideKiller::IsUpMadKiller = true;
						}
					}
				}
				else if (SuperNewRoles::RoleHelpers::isRole(player, CustomRPC::RoleId::MadKiller))
				{
					auto sideplayer = RoleClass::SideKiller::getSidePlayer(PlayerControl::LocalPlayer);
					if (sideplayer != nullptr)
					{
						SuperNewRoles::Helpers::RPCHelper::RPCSetRoleUnchecked(player, RoleTypes::Impostor);
					}
				}
			}
		}
	}
}
