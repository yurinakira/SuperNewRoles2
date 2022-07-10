#include "Fox.h"
#include "../../../CustomRPC/CustomRPC.h"
#include "../../../Roles/RoleClass.h"

using namespace HarmonyLib;
using namespace SuperNewRoles::Roles;

namespace SuperNewRoles::Mode::SuperHostRoles::Roles
{

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: public static void Postfix(HudManager __instance, [HarmonyArgument(0)] bool isActive)
	void Fox::SetHudActivePatch::Postfix(HudManager *__instance, bool isActive)
	{
		if (!AmongUsClient::Instance->AmHost)
		{
			return;
		}
		if (PlayerControl::LocalPlayer::isRole(CustomRPC::RoleId::Fox))
		{
			__instance->ReportButton.ToggleVisible(visible: RoleClass::Fox::UseReport);
		}
	}
}
