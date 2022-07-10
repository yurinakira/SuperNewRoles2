#include "EvilGambler.h"
#include "../Mode/ModeHandler.h"
#include "../CustomRPC/CustomRPC.h"
#include "RoleHelper.h"
#include "../Mode/SuperHostRoles/SyncSetting.h"
#include "RoleClass.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Mode;
using namespace SuperNewRoles::Mode::SuperHostRoles;

namespace SuperNewRoles::Roles
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Prefix(PlayerControl __instance, [HarmonyArgument(0)] PlayerControl target)
	void EvilGambler::EvilGamblerMurder::Prefix(PlayerControl *__instance, PlayerControl *target)
	{
		if (ModeHandler::isMode(std::vector<SuperNewRoles::Mode::ModeId> {ModeId::SuperHostRoles}))
		{
			if (SuperNewRoles::RoleHelpers::isRole(__instance, CustomRPC::RoleId::EvilGambler))
			{
				SyncSetting::GamblersetCool(__instance);
			}
			return;
		}
		else if (__instance == PlayerControl::LocalPlayer && SuperNewRoles::RoleHelpers::isRole(__instance, CustomRPC::RoleId::EvilGambler))
		{
			if (RoleClass::EvilGambler::GetSuc())
			{
				//成功
				PlayerControl::LocalPlayer::SetKillTimer(RoleClass::EvilGambler::SucCool);
			}
			else
			{
				//失敗
				PlayerControl::LocalPlayer::SetKillTimer(RoleClass::EvilGambler::NotSucCool);
			};
		}
	}
}
