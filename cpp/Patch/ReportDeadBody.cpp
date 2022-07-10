#include "ReportDeadBody.h"
#include "../Mode/ModeHandler.h"
#include "../CustomRPC/CustomRPC.h"
#include "../Roles/RoleHelper.h"
#include "../Helpers/RPCHelper.h"
#include "../Roles/RoleClass.h"
#include "../MapOptions/MapOption.h"
#include "../Mode/Detective/main.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::CustomRPC;
using namespace SuperNewRoles::Helpers;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Patch
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static bool Prefix(PlayerControl __instance, [HarmonyArgument(0)] GameData.PlayerInfo target)
	bool ReportDeadBody::ReportDeadBodyPatch::Prefix(PlayerControl *__instance, GameData::PlayerInfo *target)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return true;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Default}))
		{
			if (SuperNewRoles::RoleHelpers::isRole(__instance, RoleId::Amnesiac))
			{
				if (!target->Disconnected)
				{
					SuperNewRoles::Helpers::RPCHelper::RPCSetRoleUnchecked(__instance, target->Role.Role);
					if (target->Role.IsSimpleRole)
					{
						SuperNewRoles::RoleHelpers::setRoleRPC(__instance, target->Object.getRole());
					}
				}
			}
		}
		if (RoleClass::Assassin::TriggerPlayer != nullptr)
		{
			return false;
		}
		if (!MapOptions::MapOption::UseDeadBodyReport && target != nullptr)
		{
			return false;
		}
		if (!MapOptions::MapOption::UseMeetingButton && target == nullptr)
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::HideAndSeek}))
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::BattleRoyal}))
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::CopsRobbers}))
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			return Mode::SuperHostRoles::ReportDeadBody::ReportDeadBodyPatch(__instance, target);
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Zombie}))
		{
			return false;
		}
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::Detective}) && target == nullptr && Mode::Detective::main::IsNotDetectiveMeetingButton && __instance->PlayerId != Mode::Detective::main::DetectivePlayer->PlayerId)
		{
			return false;
		}
		return true;
	}
}
